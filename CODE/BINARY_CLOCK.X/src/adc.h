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
 * --- ADC Header ---
 * Authors: Eric Born and Josh Friend
 * Course: EGR326-901
 * Instructor: Dr. Andrew Sterian
 * Date: Dec 8, 2011
 -----------------------------------------------------------------------------*/

#ifndef ADC_h
#define ADC_h

#include "types.h"

//ADC result align macro defs
#define RIGHT_ALIGN 1
#define LEFT_ALIGN 0

//ADC clock prescaler macro defs
#define DIV2 0x00
#define DIV4 0x04
#define DIV8 0x01
#define DIV16 0x05
#define DIV32 0x02
#define DIV64 0x06
#define FRC 0x07

//ADC VREF+ Source macro defs
#define VREFp_VDD 0x00
#define VREFp_VREFP_PIN 0x02
#define VREFp_FVR 0x03

//FVR level macro defs
#define ADCFVR_OFF 0x00
#define ADCFVR_1V024 0x01
#define ADCFVR_2V048 0x02
#define ADCFVR_4V096 0x03

//Function Prototypes
void adc_setup(uint8_t align, uint8_t refl, uint8_t refs, uint8_t freq);
void adc_ch_sel(uint8_t ch);
void adc_en(uint8_t en);
void adc_interrupt_en(uint8_t en);
void adc_start(void);
void adc_stop(void);
uint16_t ad_read(void);

#endif
