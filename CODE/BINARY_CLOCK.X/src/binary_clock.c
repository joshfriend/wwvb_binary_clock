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
 * --- Binary Clock Hardware Source ---
 * Authors: Eric Born and Josh Friend
 * Course: EGR326-901
 * Instructor: Dr. Andrew Sterian
 * Date: Nov 2, 2011
 -----------------------------------------------------------------------------*/

#include "htc.h"
#include "binary_clock.h"

void io_setup(void) {
    //Set outputs and inputs
    TRISA = 0b00011111;
    TRISB = 0;
    TRISC = 0;

    //Turn ADC funcitonality OFF where not used
    ANSELA = 0b00000100;

    //ANSELB = 0;
    ANSELC = 0;

    //Enable weak pull-ups
    nWPUEN = 0;

    //Enable weak pull-up on RA4
    WPUA |= 0x10;
}

/*------------------------------------------------------------------------------
 * Description:
 * Initializes falling edge pin-change interrupts on gated timer input (RA4).
 *
 * Parameters:
 * none
 *
 * Returns:
 * none
 -----------------------------------------------------------------------------*/
void pcint_setup(void) {
    //Enable negative edge pin change interrupt on RA4
    IOCAN4 = 1;

    //Enable Global interrupts
    GIE = 1;

    //Enable peripheral interrupts
    PEIE = 1;
}

void write_digit(unsigned char val) {
    PORTB = (val & 0x3C) << 2;
    PORTC = (val & 0x03);
}