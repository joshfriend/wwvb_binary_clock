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
 * --- Timer Hardware Header ---
 * Authors: Eric Borne and Josh Friend
 * Course: EGR326-901
 * Instructor: Dr. Andrew Sterian
 * Date: Dec 8, 2011
 -----------------------------------------------------------------------------*/

#ifndef TIMER_HARDWARE_h
#define TIMER_HARDWARE_h

#include "types.h"

//System clock frequency
#define FOSC 1000000UL

#define PWMA = 1
#define PWMB = 2
#define PWMC = 3
#define PWMD = 4

//Function Prototypes
void timer1_init(void);
void timer2_init(void);
void timer4_init(void);
void timer6_init(void);

void pwm_setup(void);
void set_pwm1_duty(uint16_t duty_cycle);
void pwm1_sel(uint8_t sel);

#endif