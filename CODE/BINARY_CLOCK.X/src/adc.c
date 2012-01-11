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
 * --- ADC Source ---
 * Authors: Eric Born and Josh Friend
 * Course: EGR326-901
 * Instructor: Dr. Andrew Sterian
 * Date: Nov 2, 2011
 -----------------------------------------------------------------------------*/

#include "htc.h"
#include "adc.h"
#include "types.h"

void adc_setup(uint8_t align, uint8_t refl, uint8_t refs, uint8_t freq) {
    //Enable Fixed Voltage Reference (FVR)
    FVREN = 1;

    //Set FVR for the ADC
    FVRCONbits.ADFVR = refl;

    //Enable ADC
    ADON = 1;

    //Result alignment selection
    ADFM = 1;

    //Set ADC reference voltage source
    ADCON1bits.ADPREF = refs;

    //Set conversion clock
    ADCON1bits.ADCS = freq;

    //Enable ADC interrupts
    ADIE = 1;
    ADIF = 0;
    GIE = 1;
    PEIE = 1;

    //Start conversion
    ADGO = 1;
}

void adc_ch_sel(uint8_t ch) {
    //Set ADC source channel
    ADCON0bits.CHS = ch;
}

void adc_en(uint8_t en) {
    ADON = en;
    ADIE = en;
}

void adc_interrupt_en(uint8_t en) {
    ADIE = en;
}

void adc_start(void) {
    ADGO = 1;
}

void adc_stop(void) {
    ADGO = 0;
}

uint16_t ad_read(void) {
    return ADRES;
}