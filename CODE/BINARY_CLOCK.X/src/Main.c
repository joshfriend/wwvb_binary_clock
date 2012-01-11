/*------------------------------------------------------------------------------
 *  ______     __  __     ______     ______     __   __     ______
 * /\  ___\   /\ \_\ \   /\  == \   /\  __ \   /\ "-.\ \   /\  __ \
 * \ \ \____  \ \  __ \  \ \  __<   \ \ \/\ \  \ \ \-.  \  \ \ \/\ \
 *  \ \_____\  \ \_\ \_\  \ \_\ \_\  \ \_____\  \ \_\\"\_\  \ \_____\
 *   \/_____/   \/_/\/_/   \/_/ /_/   \/_____/   \/_/ \/_/   \/_____/
 *          ______   ______     __    __     __     ______
 *         /\__  _\ /\  __ \   /\ "-./  \   /\ \   /\  ___\
 *         \/_/\ \/ \ \ \/\ \  \ \ \-./\ \  \ \ \  \ \ \____
 *            \ \_\  \ \_____\  \ \_\ \ \_\  \ \_\  \ \_____\
 *             \/_/   \/_____/   \/_/  \/_/   \/_/   \/_____/
 *
 * --- WWVB Interpreter Main Source ---
 * Authors: Eric Born and Josh Friend
 * Course: EGR326-901
 * Instructor: Dr. Andrew Sterian
 * Date: Dec 8, 2011
 -----------------------------------------------------------------------------*/

#include "htc.h"
#include "timer_hardware.h"
#include "binary_clock.h"
#include "wwvb.h"
#include "types.h"
#include "calendar.h"
#include "adc.h"
//#include "mTouchCVD.h"


//Set config bits
__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & CP_OFF & CPD_OFF &
         BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
__CONFIG(WRT_OFF & PLLEN_OFF & STVREN_OFF & LVP_OFF);

//Function prototypes
void setup(void);
void mTouchISR(void);

//WWVB processing variables
volatile uint16_t tick = 0;
volatile uint16_t pulse_length = 0;
volatile uint16_t timer1_val = 0;
volatile uint8_t edge_count = 0;
volatile uint8_t bit_recieved_flag = 0;

//Display multiplexing variables
volatile uint8_t active_col = 0;
volatile uint8_t mplex_tick = 0;

//ADC variables
volatile uint16_t adc_val = 0;
volatile uint8_t adc_flag = 0;

//Timekeeping
volatile uint16_t ms_tick = 0;
volatile uint8_t hrs_digit = 15;
volatile uint8_t min_digit = 4;
volatile uint8_t sec_digit = 0;

/*------------------------------------------------------------------------------
 * Description:
 * MAIN CODE LOOP
 * Initializes harware peripherals
 * Waits for WWVB processing functions and interrupts to set flags. Main then 
 * calls the appropriate function to deal with these flags.
 *
 * Parameters:
 * none
 *
 * Returns:
 * none
 -----------------------------------------------------------------------------*/
void main(void) {
    //Run setup routines
    setup();

    //mTouchCVD_Init();

    while(1) {
        if(adc_flag) {
            //Clear flag
            adc_flag = 0;

            //Set brightness
            set_pwm1_duty((adc_val < 30) ? (1) : (adc_val << 1));


            //Show PWM brightness
            //min_digit = adc_val >> 6;
            //sec_digit = adc_val & 0x3F;
        }
        if(bit_recieved_flag == 1) {
            //Convert timer count to milliseconds (divide by 32)
            pulse_length >>= 5;

            uint8_t wwvb_bit = process_bit(pulse_length);

            //Clear flag
            bit_recieved_flag = 0;
        }
        if(frame_recieved_flag == 1) {

            //Get time data
            time_t time;
            process_frame(&time);
            
            if(validate(time)) {
                //STORE TIME
                ms_tick = 0;

                sec_digit = time.seconds;
                min_digit = time.minutes;
                hrs_digit = time.hours;
            }

            //Clear flag
            frame_recieved_flag = 0;
        }
    }
}

/*------------------------------------------------------------------------------
 * Description:
 * Interrupt service routine for the PIC16F1824.
 * Responsible for handling I2C, gated timer and Timer2 interrupt events.
 * This ISR handles the timing of the WWVB radio input.
 *
 * Parameters:
 * none
 *
 * Returns:
 * none
 -----------------------------------------------------------------------------*/
void interrupt isr (void) {
    //RA4 Pin change interrupt event
    if(IOCAF4 && IOCAN4) {
        //Beginning of bit
        if(edge_count == 0) {
            TMR1 = 0;
            tick = 0;
            edge_count++;
        }
        else {
            //Check to see that transition occured inside width of one bit
            if(tick <= MIN_BIT_WIDTH_MS) {
                //Increment edge count
                edge_count++;
            }
            //Edge outside bit width, reset
            else if(tick >= BIT_TIMEOUT_MS) {
                edge_count = 0;
            }
            //End of bit/beginning of new bit
            else {
                //set flag recieved bit
                bit_recieved_flag = 1;
                
                //Save length of bit
                if(edge_count > MAX_EDGES) {
                    pulse_length = 0;
                }
                else {
                    pulse_length = TMR1;
                }

                //Reset timers
                TMR1 = 0;
                tick = 0;

                //Reset edge count
                edge_count = 1;
            }
        }
        
        //Clear interrupt flag
        IOCAF4 = 0;
    }

    //Timer2 compare match event
    if(TMR2IE && TMR2IF) {
        //Clear interrupt flag
        TMR2IF = 0;

        //Increment tick
        tick++;

        //Update time
        if(ms_tick++ == 1000) {
            ms_tick = 0;
            sec_digit++;
        }
        if(sec_digit == 60) {
            sec_digit = 0;
            min_digit++;
        }
        if(min_digit == 60) {
            min_digit = 0;
            hrs_digit++;
        }
        if(hrs_digit == 24) {
            hrs_digit = 0;
        }
    }

    //Timer2 compare match event
    if(TMR4IE && TMR4IF) {
        //Clear interrupt flag
        TMR4IF = 0;

        if(mplex_tick++ == 3) {
            mplex_tick = 0;
            
            //Multiplex display:
            if(active_col == HOURS_COL) {
                active_col = MINUTES_COL;

                //Turn OFF first to prevent ghosting
                write_digit(0);
                pwm1_sel(0);

                //Write next digit
                pwm1_sel(active_col);
                write_digit(min_digit);
            }
            else if(active_col == MINUTES_COL) {
                active_col = SECONDS_COL;

                //Turn OFF first to prevent ghosting
                write_digit(0);
                pwm1_sel(0);

                //Write next digit
                pwm1_sel(active_col);
                write_digit(sec_digit);
            }
            else {
                active_col = HOURS_COL;

                //Turn OFF first to prevent ghosting
                write_digit(0);
                pwm1_sel(0);

                //Write next digit
                pwm1_sel(active_col);
                write_digit(hrs_digit);
            }
        }
    }
    
    //ADC conversion complete event
    if(ADIF && ADIE) {
        //Clear interrupt flag
        ADIF = 0;

        //Set flag
        adc_flag = 1;

        //Store ADC result
        //Subtract complete darkness reading value
        adc_val = ADRES;
        if(adc_val < 700) {
            adc_val = 0;
        }
        else {
            adc_val -= 700;
        }

        //Start new conversion
        ADGO = 1;
    }

    //mTouchISR();
}

/*------------------------------------------------------------------------------
 * Description:
 * Initializes the main oscilator hardware and interrupts
 * Main clock frequency FOSC is set to 1 MHz
 *
 * Parameters:
 * none
 *
 * Returns:
 * none
 -----------------------------------------------------------------------------*/
void setup(void) {
    //Disable watchdog timer
    SWDTEN = 0;

    //Set primary clock frequency to 1MHz
    //OSCCON = IRCF3 + IRCF1 + IRCF0 + SCS1;
    OSCCON = 0b01011010;

    //Enable global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
    
    //Initialize IO
    io_setup();

    //Initialize timer hardware
    timer1_init();  //WWVB Processing
    timer2_init();  //WWVB Processing/Timekeeping
    timer4_init();  //PWM/Multiplexing

    //Initialize pin change interrupts
    pcint_setup();

    //Initialize PWM
    pwm_setup();

    //Initialize ADC
    adc_setup(RIGHT_ALIGN, ADCFVR_1V024, VREFp_FVR, DIV2);
    adc_ch_sel(0x02);
}