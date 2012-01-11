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
 * --- Timer Hardware Source ---
 * Authors: Eric Born and Josh Friend
 * Course: EGR326-901
 * Instructor: Dr. Andrew Sterian
 * Date: Dec 8, 2011
 -----------------------------------------------------------------------------*/

#include "htc.h"
#include "types.h"
#include "timer_hardware.h"

//CPU Frequency
#define FOSC 1000000UL

void timer0_init(void) {
    //Timer2 ON, 1/1 prescaler = 4us per tick
    TMR2ON = 1;

    //Enable Timer2 Interrupts
    TMR2IE = 1;

    //Clear interrupt flag
    TMR2IF = 0;

    //Enable Global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
}

/*------------------------------------------------------------------------------
 * Description:
 * Initializes the Timer1 peripheral on the PIC. The Chrono-tomic Arduino
 * Shield uses the gate feature on RA4 to control this timer. 
 * Gated count mode is enabled with polarity 0 to count when gate pin is LOW.
 * Prescaler is set to FOSC/4 to enable the Timer to measure at least a 1 sec
 * range required by WWVB interpreter algorithm.
 *
 * Parameters:
 * none
 *
 * Returns:
 * none
 -----------------------------------------------------------------------------*/
void timer1_init(void) {
    //Timer ON, 1/8 Prescaler, Source = FOSC/4, 2 second range
    TMR1ON = 1;
    T1CKPS1 = 1;
    T1CKPS0 = 1;

    //Enable gate on T1G pin, active LOW.
    TMR1GE = 1;
    T1GPOL = 0;

    //Enable Global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
}

/*------------------------------------------------------------------------------
 * Description:
 * Initializes the Timer2 peripheral on the PIC. This timer is setup to trigger
 * an interrupt every millisecond for general timing purposes.
 *
 * Parameters:
 * none
 *
 * Returns:
 * none
 -----------------------------------------------------------------------------*/
void timer2_init(void) {
    //Timer2 ON, 1/1 prescaler = 4us per tick
    TMR2ON = 1;

    //Timer2 compare match set to create 1ms interrupt tick
    PR2 = ((FOSC / 4) / 1) / 1000 - 1;

    //Enable Timer2 Interrupts
    TMR2IE = 1;

    //Clear interrupt flag
    TMR2IF = 0;

    //Enable Global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
}

void timer4_init(void) {
    //Timer4 ON, 1/1 prescaler = 4us per tick
    TMR4ON = 1;

    //Max PWM value and interrupt interval for multiplexing
    PR4 = 0xFF;

    //Enable Timer4 Interrupts
    TMR4IE = 1;

    //Clear interrupt flag
    TMR4IF = 0;

    //Enable Global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
}

void timer6_init(void) {
    //Timer2 ON, 1/1 prescaler = 4us per tick
    TMR6ON = 1;

    //Timer2 compare match set to create 1ms interrupt tick
    PR6 = ((FOSC / 4) / 1) / 1000 - 1;

    //Enable Timer2 Interrupts
    TMR6IE = 1;

    //Clear interrupt flag
    TMR6IF = 0;

    //Enable Global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
}

void pwm_setup(void) {
    //Set PWM mode to "toggle on output match"
    CCP1CONbits.CCP1M = 0x0C;

    //Set source for CCP1 PWM to Timer4
    CCPTMRSbits.C1TSEL = 0x01;

    //Disable autoshutdown features
    CCP1AS = 0x00;

    //Setup APFCON so that P1D is on RC2
    P1DSEL = 0;
}

void set_pwm1_duty(uint16_t duty_cycle) {
    //Avoid overflowing max value of 10bit PWM
    if(duty_cycle > 1024) {
        duty_cycle = 1024;
    }

    //Set 10bit PWM duty cycle value
    CCPR1L = (duty_cycle >> 2);
    CCP1CONbits.DC1B = (duty_cycle & 0x03);
}

void pwm1_sel(uint8_t sel) {

    //Blank out PORTC data
    RC5 = RC4 = RC2 = 0;

    switch(sel) {
        case 0:
            //Turns PWM off
            PSTR1CON = 0x00;
            break;
        case 1:
            PSTR1CON = 0x01;
            break;
        case 2:
            PSTR1CON = 0x02;
            break;
        case 3:\
            PSTR1CON = 0x04;
            break;
        case 4:
            PSTR1CON = 0x08;
            break;
        case 5:
            PSTR1CON = 0b00011011;
            break;
    }
}