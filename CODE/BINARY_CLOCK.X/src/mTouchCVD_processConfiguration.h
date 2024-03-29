/*************************************************************************
 *  � 2011 Microchip Technology Inc.                                       
 *  
 *  Project Name:    mTouch CVD Framework v1.1
 *  FileName:        mTouchCVD_processConfiguration.h
 *
 *  Processor:       See documentation for supported PIC� microcontrollers 
 *  Compiler:        HI-TECH Ver. 9.81 or later
 *  IDE:             MPLAB� IDE v8.50 (or later) or MPLAB� X                        
 *  Hardware:         
 *  Company:         
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Description:     mTouch CVD Framework Include File
 *                   - No application code should be implemented in this
 *                     or any other mTouch framework file. This will allow
 *                     for better customer support and easier upgrades to
 *                     later firmware versions. Use the main.c and user-
 *                     generated files to implement your application.
 *                   - See the documentation located in the docs/ folder
 *                     for a more information about how the framework is
 *                     implemented.
 *************************************************************************/
/**************************************************************************
 * MICROCHIP SOFTWARE NOTICE AND DISCLAIMER: You may use this software, and 
 * any derivatives created by any person or entity by or on your behalf, 
 * exclusively with Microchip's products in accordance with applicable
 * software license terms and conditions, a copy of which is provided for
 * your referencein accompanying documentation. Microchip and its licensors 
 * retain all ownership and intellectual property rights in the 
 * accompanying software and in all derivatives hereto. 
 * 
 * This software and any accompanying information is for suggestion only. 
 * It does not modify Microchip's standard warranty for its products. You 
 * agree that you are solely responsible for testing the software and 
 * determining its suitability. Microchip has no obligation to modify, 
 * test, certify, or support the software. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH 
 * MICROCHIP'S PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY 
 * APPLICATION. 
 * 
 * IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, 
 * TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT 
 * LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, 
 * SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, 
 * FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, 
 * HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY 
 * OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
 * MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS 
 * SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID 
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE. 
 * 
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF 
 * THESE TERMS. 
 *************************************************************************/
/** @file mTouchCVD_processConfiguration.h
* @brief Internal framework header file performing many pre-compiler checks
*
* Also, performs setup and error checking operations at compile time.
*/
#ifndef __MTOUCHCVD_PROCESSCONFIGURATION_H
#define __MTOUCHCVD_PROCESSCONFIGURATION_H


/// @cond

#define     __paste1(a,b)                   a##b
#define     __paste(a,b)                    __paste1(a,b) 

#if defined(CVD_Board_Revision) && defined(CVD_Software_Revision)
    #define CVD_Firmware_Version    ((CVD_Board_Revision << 8) | CVD_Software_Revision)
#endif

#if !defined(RELEASE_THRESHOLD_FACTOR)
    #warning RELEASE_THRESHOLD_FACTOR must be defined in the configuration file. Setting to '0.5'.
    #define RELEASE_THRESHOLD_FACTOR 0.5
#endif
#if defined(AVG_UPDATE)
    #if ((AVG_UPDATE != 0) && (AVG_UPDATE != 1) && (AVG_UPDATE != 2) && (AVG_UPDATE != 4) && (AVG_UPDATE != 8) && (AVG_UPDATE != 16))
        #warning Invalid value for AVG_UPDATE. AVG_ENABLE has been turned off.
        #undef AVG_UPDATE
        #undef AVG_ENABLE
    #elif ((AVG_UPDATE == 0) || (AVG_UPDATE == 1))
        #undef AVG_ENABLE
    #endif
#endif
#if !defined(POWER_UP_SAMPLES)
    #warning POWER_UP_SAMPLES must be defined in the configuration file. Setting to '50'.
    #define POWER_UP_SAMPLES 50
#else
    #if POWER_UP_SAMPLES > 65535
        #warning POWER_UP_SAMPLES exceeds the maximum limit of 65535. Setting to '65535'.
        #undef POWER_UP_SAMPLES
        #define POWER_UP_SAMPLES 65535
    #endif
    #if POWER_UP_SAMPLES < 1
        #warning POWER_UP_SAMPLES must be at least '1'. Setting to '1'.
        #undef POWER_UP_SAMPLES
        #define POWER_UP_SAMPLES 1
    #endif
#endif
#if defined (BUTTON_TIMEOUT)
    #if BUTTON_TIMEOUT > 255
        #warning BUTTON_TIMEOUT exceeds the maximum limit of 255. Setting to '255'.
        #undef BUTTON_TIMEOUT
        #define BUTTON_TIMEOUT 255
    #endif
#endif
#if !defined(DEBOUNCE_COUNT_RELEASE)
    #define DEBOUNCE_COUNT_RELEASE 1
#else
    #if DEBOUNCE_COUNT_RELEASE > 255
        #warning DEBOUNCE_COUNT_RELEASE exceeds the maximum limit of 255. Setting to '255'.
        #undef DEBOUNCE_COUNT_RELEASE
        #define DEBOUNCE_COUNT_RELEASE 255
    #endif
    #if DEBOUNCE_COUNT_RELEASE < 1
        #warning DEBOUNCE_COUNT_RELEASE must be at least '1'. Setting to '1'.
        #undef DEBOUNCE_COUNT_RELEASE
        #define DEBOUNCE_COUNT_RELEASE 1
    #endif
#endif
#if !defined(DEBOUNCE_COUNT_PRESS)
    #define DEBOUNCE_COUNT_PRESS 1
#else
    #if DEBOUNCE_COUNT_PRESS > 255
        #warning DEBOUNCE_COUNT_PRESS exceeds the maximum limit of 255. Setting to '255'.
        #undef DEBOUNCE_COUNT_PRESS
        #define DEBOUNCE_COUNT_PRESS 255
    #endif
    #if DEBOUNCE_COUNT_PRESS < 1
        #warning DEBOUNCE_COUNT_PRESS must be at least '1'. Setting to '1'.
        #undef DEBOUNCE_COUNT_PRESS
        #define DEBOUNCE_COUNT_PRESS 1
    #endif
#endif
#if !defined(CVD_JITTER_TYPE) || ((CVD_JITTER_TYPE != 1) && (CVD_JITTER_TYPE != 0))
    #warning CVD_JITTER_TYPE set to an invalid value. Setting to '0'.
    #undef CVD_JITTER_TYPE
    #define CVD_JITTER_TYPE 0
#endif
#if !defined(CVD_SAMPLES_PER_SCAN)
    #warning CVD_SAMPLES_PER_SCAN must be defined in the configuration file. Defaulting to 20ms timing.
    #define CVD_SAMPLES_PER_SCAN CVD_20ms_Timing
#endif
#if !defined(_XTAL_FREQ)
    #error _XTAL_FREQ is not defined in the configuration file. Framework must be told how fast Fosc is running.
#endif
#if !defined(TMR0_PRESCALER)
    #warning TMR0_PRESCALER is not defined in the configuration file. Framework must be told this prescaler value. Assuming 1:1.
    #define TMR0_PRESCALER 1
#endif
#if TMR0_PRESCALER == 1
    #warning TMR0 Prescaler of 1:1 means the system will spend 62% of its time in the ISR. If desired, you can increase the prescaler to reduce this percentage.
#endif
#if !defined(CVD_SENSOR0)
    #error There is no CVD_SENSOR0 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
#endif
#if !defined(NEGATIVE_CAPACITANCE)
    #define NEGATIVE_CAPACITANCE 0
#endif
#if (NEGATIVE_CAPACITANCE != 0) && (NEGATIVE_CAPACITANCE != 1) && (NEGATIVE_CAPACITANCE != 2)
    #warning NEGATIVE_CAPACITANCE is set to an invalid value. Defaulting to 0.
    #undef NEGATIVE_CAPACITANCE
    #define NEGATIVE_CAPACITANCE 0
#endif

#if CVD_NUMBER_SENSORS > 1
    #if !defined(CVD_SENSOR1)
        #error There is no CVD_SENSOR1 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 2
    #if !defined(CVD_SENSOR2)
        #error There is no CVD_SENSOR2 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 3
    #if !defined(CVD_SENSOR3)
        #error There is no CVD_SENSOR3 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 4
    #if !defined(CVD_SENSOR4)
        #error There is no CVD_SENSOR4 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 5
    #if !defined(CVD_SENSOR5)
        #error There is no CVD_SENSOR5 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 6
    #if !defined(CVD_SENSOR6)
        #error There is no CVD_SENSOR6 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 7
    #if !defined(CVD_SENSOR7)
        #error There is no CVD_SENSOR7 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 8
    #if !defined(CVD_SENSOR8)
        #error There is no CVD_SENSOR8 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 9
    #if !defined(CVD_SENSOR9)
        #error There is no CVD_SENSOR9 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 10
    #if !defined(CVD_SENSOR10)
        #error There is no CVD_SENSOR10 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 11
    #if !defined(CVD_SENSOR11)
        #error There is no CVD_SENSOR11 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 12
    #if !defined(CVD_SENSOR12)
        #error There is no CVD_SENSOR12 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 13
    #if !defined(CVD_SENSOR13)
        #error There is no CVD_SENSOR13 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 14
    #if !defined(CVD_SENSOR14)
        #error There is no CVD_SENSOR14 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 15
    #if !defined(CVD_SENSOR15)
        #error There is no CVD_SENSOR15 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 16
    #if !defined(CVD_SENSOR16)
        #error There is no CVD_SENSOR16 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 17
    #if !defined(CVD_SENSOR17)
        #error There is no CVD_SENSOR17 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 18
    #if !defined(CVD_SENSOR18)
        #error There is no CVD_SENSOR18 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 19
    #if !defined(CVD_SENSOR19)
        #error There is no CVD_SENSOR19 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 20
    #if !defined(CVD_SENSOR20)
        #error There is no CVD_SENSOR20 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 21
    #if !defined(CVD_SENSOR21)
        #error There is no CVD_SENSOR21 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 22
    #if !defined(CVD_SENSOR22)
        #error There is no CVD_SENSOR22 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 23
    #if !defined(CVD_SENSOR23)
        #error There is no CVD_SENSOR23 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 24
    #if !defined(CVD_SENSOR24)
        #error There is no CVD_SENSOR24 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 25
    #if !defined(CVD_SENSOR25)
        #error There is no CVD_SENSOR25 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 26
    #if !defined(CVD_SENSOR26)
        #error There is no CVD_SENSOR26 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 27
    #if !defined(CVD_SENSOR27)
        #error There is no CVD_SENSOR27 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 28
    #if !defined(CVD_SENSOR28)
        #error There is no CVD_SENSOR28 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 29
    #if !defined(CVD_SENSOR29)
        #error There is no CVD_SENSOR29 definition in the configuration file. Framework unable to associate the sensor with an analog pin.
    #endif
#endif
#if CVD_NUMBER_SENSORS > 30
    #error This version of the mTouch CVD Framework does not support more than 30 sensors at this time.
#endif

#if !defined(THRESHOLD_PRESS_SENSOR0)
    #if CVD_NUMBER_SENSORS > 0
        #error Required definition, THRESHOLD_PRESS_SENSOR0, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR0 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR1)
    #if CVD_NUMBER_SENSORS > 1
        #error Required definition, THRESHOLD_PRESS_SENSOR1, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR1 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR2)
    #if CVD_NUMBER_SENSORS > 2
        #error Required definition, THRESHOLD_PRESS_SENSOR2, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR2 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR3)
    #if CVD_NUMBER_SENSORS > 3
        #error Required definition, THRESHOLD_PRESS_SENSOR3, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR3 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR4)
    #if CVD_NUMBER_SENSORS > 4
        #error Required definition, THRESHOLD_PRESS_SENSOR4, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR4 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR5)
    #if CVD_NUMBER_SENSORS > 5
        #error Required definition, THRESHOLD_PRESS_SENSOR5, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR5 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR6)
    #if CVD_NUMBER_SENSORS > 6
        #error Required definition, THRESHOLD_PRESS_SENSOR6, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR6 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR7)
    #if CVD_NUMBER_SENSORS > 7
        #error Required definition, THRESHOLD_PRESS_SENSOR7, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR7 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR8)
    #if CVD_NUMBER_SENSORS > 8
        #error Required definition, THRESHOLD_PRESS_SENSOR8, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR8 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR9)
    #if CVD_NUMBER_SENSORS > 9
        #error Required definition, THRESHOLD_PRESS_SENSOR9, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR9 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR10)
    #if CVD_NUMBER_SENSORS > 10
        #error Required definition, THRESHOLD_PRESS_SENSOR10, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR10 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR11)
    #if CVD_NUMBER_SENSORS > 11
        #error Required definition, THRESHOLD_PRESS_SENSOR11, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR11 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR12)
    #if CVD_NUMBER_SENSORS > 12
        #error Required definition, THRESHOLD_PRESS_SENSOR12, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR12 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR13)
    #if CVD_NUMBER_SENSORS > 13
        #error Required definition, THRESHOLD_PRESS_SENSOR13, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR13 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR14)
    #if CVD_NUMBER_SENSORS > 14
        #error Required definition, THRESHOLD_PRESS_SENSOR14, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR14 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR15)
    #if CVD_NUMBER_SENSORS > 15
        #error Required definition, THRESHOLD_PRESS_SENSOR15, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR15 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR16)
    #if CVD_NUMBER_SENSORS > 16
        #error Required definition, THRESHOLD_PRESS_SENSOR16, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR16 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR17)
    #if CVD_NUMBER_SENSORS > 17
        #error Required definition, THRESHOLD_PRESS_SENSOR17, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR17 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR18)
    #if CVD_NUMBER_SENSORS > 18
        #error Required definition, THRESHOLD_PRESS_SENSOR18, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR18 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR19)
    #if CVD_NUMBER_SENSORS > 19
        #error Required definition, THRESHOLD_PRESS_SENSOR19, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR19 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR20)
    #if CVD_NUMBER_SENSORS > 20
        #error Required definition, THRESHOLD_PRESS_SENSOR20, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR20 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR21)
    #if CVD_NUMBER_SENSORS > 21
        #error Required definition, THRESHOLD_PRESS_SENSOR21, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR21 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR22)
    #if CVD_NUMBER_SENSORS > 22
        #error Required definition, THRESHOLD_PRESS_SENSOR22, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR22 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR23)
    #if CVD_NUMBER_SENSORS > 23
        #error Required definition, THRESHOLD_PRESS_SENSOR23, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR23 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR24)
    #if CVD_NUMBER_SENSORS > 24
        #error Required definition, THRESHOLD_PRESS_SENSOR24, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR24 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR25)
    #if CVD_NUMBER_SENSORS > 25
        #error Required definition, THRESHOLD_PRESS_SENSOR25, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR25 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR26)
    #if CVD_NUMBER_SENSORS > 26
        #error Required definition, THRESHOLD_PRESS_SENSOR26, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR26 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR27)
    #if CVD_NUMBER_SENSORS > 27
        #error Required definition, THRESHOLD_PRESS_SENSOR27, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR27 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR28)
    #if CVD_NUMBER_SENSORS > 28
        #error Required definition, THRESHOLD_PRESS_SENSOR28, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR28 0
    #endif
#endif
#if !defined(THRESHOLD_PRESS_SENSOR29)
    #if CVD_NUMBER_SENSORS > 29
        #error Required definition, THRESHOLD_PRESS_SENSOR29, is not defined in the configuration file.
    #else
        #define THRESHOLD_PRESS_SENSOR29 0
    #endif
#endif

#define THRESHOLD_RELEASE_SENSOR0       (unsigned int)((float) THRESHOLD_PRESS_SENSOR0  * RELEASE_THRESHOLD_FACTOR)                                             
#define THRESHOLD_RELEASE_SENSOR1       (unsigned int)((float) THRESHOLD_PRESS_SENSOR1  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR2       (unsigned int)((float) THRESHOLD_PRESS_SENSOR2  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR3       (unsigned int)((float) THRESHOLD_PRESS_SENSOR3  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR4       (unsigned int)((float) THRESHOLD_PRESS_SENSOR4  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR5       (unsigned int)((float) THRESHOLD_PRESS_SENSOR5  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR6       (unsigned int)((float) THRESHOLD_PRESS_SENSOR6  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR7       (unsigned int)((float) THRESHOLD_PRESS_SENSOR7  * RELEASE_THRESHOLD_FACTOR)  
#define THRESHOLD_RELEASE_SENSOR8       (unsigned int)((float) THRESHOLD_PRESS_SENSOR8  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR9       (unsigned int)((float) THRESHOLD_PRESS_SENSOR9  * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR10      (unsigned int)((float) THRESHOLD_PRESS_SENSOR10 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR11      (unsigned int)((float) THRESHOLD_PRESS_SENSOR11 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR12      (unsigned int)((float) THRESHOLD_PRESS_SENSOR12 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR13      (unsigned int)((float) THRESHOLD_PRESS_SENSOR13 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR14      (unsigned int)((float) THRESHOLD_PRESS_SENSOR14 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR15      (unsigned int)((float) THRESHOLD_PRESS_SENSOR15 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR16      (unsigned int)((float) THRESHOLD_PRESS_SENSOR16 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR17      (unsigned int)((float) THRESHOLD_PRESS_SENSOR17 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR18      (unsigned int)((float) THRESHOLD_PRESS_SENSOR18 * RELEASE_THRESHOLD_FACTOR) 
#define THRESHOLD_RELEASE_SENSOR19      (unsigned int)((float) THRESHOLD_PRESS_SENSOR19 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR20      (unsigned int)((float) THRESHOLD_PRESS_SENSOR20 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR21      (unsigned int)((float) THRESHOLD_PRESS_SENSOR21 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR22      (unsigned int)((float) THRESHOLD_PRESS_SENSOR22 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR23      (unsigned int)((float) THRESHOLD_PRESS_SENSOR23 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR24      (unsigned int)((float) THRESHOLD_PRESS_SENSOR24 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR25      (unsigned int)((float) THRESHOLD_PRESS_SENSOR25 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR26      (unsigned int)((float) THRESHOLD_PRESS_SENSOR26 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR27      (unsigned int)((float) THRESHOLD_PRESS_SENSOR27 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR28      (unsigned int)((float) THRESHOLD_PRESS_SENSOR28 * RELEASE_THRESHOLD_FACTOR)
#define THRESHOLD_RELEASE_SENSOR29      (unsigned int)((float) THRESHOLD_PRESS_SENSOR29 * RELEASE_THRESHOLD_FACTOR)

#if CVD_NUMBER_SENSORS == 1
    #define CVD_SENSOR0_REFERENCE 0
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0}
#endif
#if CVD_NUMBER_SENSORS == 2
    #define CVD_SENSOR0_REFERENCE 1
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1}
#endif
#if CVD_NUMBER_SENSORS == 3
    #define CVD_SENSOR0_REFERENCE 2
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2}
#endif
#if CVD_NUMBER_SENSORS == 4
    #define CVD_SENSOR0_REFERENCE 3
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3}
#endif
#if CVD_NUMBER_SENSORS == 5
    #define CVD_SENSOR0_REFERENCE 4
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4}
#endif
#if CVD_NUMBER_SENSORS == 6
    #define CVD_SENSOR0_REFERENCE 5
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5}
#endif
#if CVD_NUMBER_SENSORS == 7
    #define CVD_SENSOR0_REFERENCE 6
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6}
#endif
#if CVD_NUMBER_SENSORS == 8
    #define CVD_SENSOR0_REFERENCE 7
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7}
#endif
#if CVD_NUMBER_SENSORS == 9
    #define CVD_SENSOR0_REFERENCE 8
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8}
#endif
#if CVD_NUMBER_SENSORS == 10
    #define CVD_SENSOR0_REFERENCE 9
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9}
#endif
#if CVD_NUMBER_SENSORS == 11
    #define CVD_SENSOR0_REFERENCE 10
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10}
#endif
#if CVD_NUMBER_SENSORS == 12
    #define CVD_SENSOR0_REFERENCE 11
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11}
#endif
#if CVD_NUMBER_SENSORS == 13
    #define CVD_SENSOR0_REFERENCE 12
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12}
#endif
#if CVD_NUMBER_SENSORS == 14
    #define CVD_SENSOR0_REFERENCE 13
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13}
#endif
#if CVD_NUMBER_SENSORS == 15
    #define CVD_SENSOR0_REFERENCE 14
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14}
#endif
#if CVD_NUMBER_SENSORS == 16
    #define CVD_SENSOR0_REFERENCE 15
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15}
#endif
#if CVD_NUMBER_SENSORS == 17
    #define CVD_SENSOR0_REFERENCE 16
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16}
#endif
#if CVD_NUMBER_SENSORS == 18
    #define CVD_SENSOR0_REFERENCE 17
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17}
#endif
#if CVD_NUMBER_SENSORS == 19
    #define CVD_SENSOR0_REFERENCE 18
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18}
#endif
#if CVD_NUMBER_SENSORS == 20
    #define CVD_SENSOR0_REFERENCE 19
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19}
#endif
#if CVD_NUMBER_SENSORS == 21
    #define CVD_SENSOR0_REFERENCE 20
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20}
#endif
#if CVD_NUMBER_SENSORS == 22
    #define CVD_SENSOR0_REFERENCE 21
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21}
#endif
#if CVD_NUMBER_SENSORS == 23
    #define CVD_SENSOR0_REFERENCE 22
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22}
#endif
#if CVD_NUMBER_SENSORS == 24
    #define CVD_SENSOR0_REFERENCE 23
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23}
#endif
#if CVD_NUMBER_SENSORS == 25
    #define CVD_SENSOR0_REFERENCE 24
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23,THRESHOLD_PRESS_SENSOR24}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23,THRESHOLD_RELEASE_SENSOR24}
#endif
#if CVD_NUMBER_SENSORS == 26
    #define CVD_SENSOR0_REFERENCE 25
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23,THRESHOLD_PRESS_SENSOR24,THRESHOLD_PRESS_SENSOR25}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23,THRESHOLD_RELEASE_SENSOR24,THRESHOLD_RELEASE_SENSOR25}
#endif
#if CVD_NUMBER_SENSORS == 27
    #define CVD_SENSOR0_REFERENCE 26
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23,THRESHOLD_PRESS_SENSOR24,THRESHOLD_PRESS_SENSOR25,THRESHOLD_PRESS_SENSOR26}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23,THRESHOLD_RELEASE_SENSOR24,THRESHOLD_RELEASE_SENSOR25,THRESHOLD_RELEASE_SENSOR26}
#endif
#if CVD_NUMBER_SENSORS == 28
    #define CVD_SENSOR0_REFERENCE 27
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23,THRESHOLD_PRESS_SENSOR24,THRESHOLD_PRESS_SENSOR25,THRESHOLD_PRESS_SENSOR26,THRESHOLD_PRESS_SENSOR27}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23,THRESHOLD_RELEASE_SENSOR24,THRESHOLD_RELEASE_SENSOR25,THRESHOLD_RELEASE_SENSOR26,THRESHOLD_RELEASE_SENSOR27}
#endif
#if CVD_NUMBER_SENSORS == 29
    #define CVD_SENSOR0_REFERENCE 28
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23,THRESHOLD_PRESS_SENSOR24,THRESHOLD_PRESS_SENSOR25,THRESHOLD_PRESS_SENSOR26,THRESHOLD_PRESS_SENSOR27,THRESHOLD_PRESS_SENSOR28}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23,THRESHOLD_RELEASE_SENSOR24,THRESHOLD_RELEASE_SENSOR25,THRESHOLD_RELEASE_SENSOR26,THRESHOLD_RELEASE_SENSOR27,THRESHOLD_RELEASE_SENSOR28}
#endif
#if CVD_NUMBER_SENSORS == 30
    #define CVD_SENSOR0_REFERENCE 29
    #define PRESS_THRESHOLD_INIT {THRESHOLD_PRESS_SENSOR0,THRESHOLD_PRESS_SENSOR1,THRESHOLD_PRESS_SENSOR2,THRESHOLD_PRESS_SENSOR3,THRESHOLD_PRESS_SENSOR4,THRESHOLD_PRESS_SENSOR5,THRESHOLD_PRESS_SENSOR6,THRESHOLD_PRESS_SENSOR7,THRESHOLD_PRESS_SENSOR8,THRESHOLD_PRESS_SENSOR9,THRESHOLD_PRESS_SENSOR10,THRESHOLD_PRESS_SENSOR11,THRESHOLD_PRESS_SENSOR12,THRESHOLD_PRESS_SENSOR13,THRESHOLD_PRESS_SENSOR14,THRESHOLD_PRESS_SENSOR15,THRESHOLD_PRESS_SENSOR16,THRESHOLD_PRESS_SENSOR17,THRESHOLD_PRESS_SENSOR18,THRESHOLD_PRESS_SENSOR19,THRESHOLD_PRESS_SENSOR20,THRESHOLD_PRESS_SENSOR21,THRESHOLD_PRESS_SENSOR22,THRESHOLD_PRESS_SENSOR23,THRESHOLD_PRESS_SENSOR24,THRESHOLD_PRESS_SENSOR25,THRESHOLD_PRESS_SENSOR26,THRESHOLD_PRESS_SENSOR27,THRESHOLD_PRESS_SENSOR28,THRESHOLD_PRESS_SENSOR29}
    #define RELEASE_THRESHOLD_INIT {THRESHOLD_RELEASE_SENSOR0,THRESHOLD_RELEASE_SENSOR1,THRESHOLD_RELEASE_SENSOR2,THRESHOLD_RELEASE_SENSOR3,THRESHOLD_RELEASE_SENSOR4,THRESHOLD_RELEASE_SENSOR5,THRESHOLD_RELEASE_SENSOR6,THRESHOLD_RELEASE_SENSOR7,THRESHOLD_RELEASE_SENSOR8,THRESHOLD_RELEASE_SENSOR9,THRESHOLD_RELEASE_SENSOR10,THRESHOLD_RELEASE_SENSOR11,THRESHOLD_RELEASE_SENSOR12,THRESHOLD_RELEASE_SENSOR13,THRESHOLD_RELEASE_SENSOR14,THRESHOLD_RELEASE_SENSOR15,THRESHOLD_RELEASE_SENSOR16,THRESHOLD_RELEASE_SENSOR17,THRESHOLD_RELEASE_SENSOR18,THRESHOLD_RELEASE_SENSOR19,THRESHOLD_RELEASE_SENSOR20,THRESHOLD_RELEASE_SENSOR21,THRESHOLD_RELEASE_SENSOR22,THRESHOLD_RELEASE_SENSOR23,THRESHOLD_RELEASE_SENSOR24,THRESHOLD_RELEASE_SENSOR25,THRESHOLD_RELEASE_SENSOR26,THRESHOLD_RELEASE_SENSOR27,THRESHOLD_RELEASE_SENSOR28,THRESHOLD_RELEASE_SENSOR29}
#endif

#define NOP0    
#define NOP1     asm("nop");
#define NOP2     NOP1;  NOP1;
#define NOP3     NOP2;  NOP1;
#define NOP4     NOP3;  NOP1;
#define NOP5     NOP4;  NOP1;
#define NOP6     NOP5;  NOP1;
#define NOP7     NOP6;  NOP1;
#define NOP8     NOP7;  NOP1;
#define NOP9     NOP8;  NOP1;
#define NOP10    NOP9;  NOP1;
#define NOP11   NOP10;  NOP1;
#define NOP12   NOP11;  NOP1;
#define NOP13   NOP12;  NOP1;
#define NOP14   NOP13;  NOP1;
#define NOP15   NOP14;  NOP1;
#define NOP16   NOP15;  NOP1;
#define NOP17   NOP16;  NOP1;
#define NOP18   NOP17;  NOP1;
#define NOP19   NOP18;  NOP1;
#define NOP20   NOP19;  NOP1;
#define NOP21   NOP20;  NOP1;
#define NOP22   NOP21;  NOP1;
#define NOP23   NOP22;  NOP1;
#define NOP24   NOP23;  NOP1;
#define NOP25   NOP24;  NOP1;
#define NOP26   NOP25;  NOP1;
#define NOP27   NOP26;  NOP1;
#define NOP28   NOP27;  NOP1;
#define NOP29   NOP28;  NOP1;
#define NOP30   NOP29;  NOP1;
#define NOP31   NOP30;  NOP1;
#define NOP32   NOP31;  NOP1;
#define NOP33   NOP32;  NOP1;
#define NOP34   NOP33;  NOP1;
#define NOP35   NOP34;  NOP1;
#define NOP36   NOP35;  NOP1;
#define NOP37   NOP36;  NOP1;
#define NOP38   NOP37;  NOP1;
#define NOP39   NOP38;  NOP1;
#define NOP40   NOP39;  NOP1;
#define NOP41   NOP40;  NOP1;
#define NOP42   NOP41;  NOP1;
#define NOP43   NOP42;  NOP1;
#define NOP44   NOP43;  NOP1;
#define NOP45   NOP44;  NOP1;
#define NOP46   NOP45;  NOP1;
#define NOP47   NOP46;  NOP1;
#define NOP48   NOP47;  NOP1;
#define NOP49   NOP48;  NOP1;
#define NOP50   NOP49;  NOP1;
#define NOP51   NOP50;  NOP1;
#define NOP52   NOP50;  NOP2;
#define NOP53   NOP50;  NOP3;
#define NOP54   NOP50;  NOP4;
#define NOP55   NOP50;  NOP5;
#define NOP56   NOP50;  NOP6;
#define NOP57   NOP50;  NOP7;
#define NOP58   NOP50;  NOP8;
#define NOP59   NOP50;  NOP9;
#define NOP60   NOP50; NOP10;
#define NOP61   NOP50; NOP10; NOP1;
#define NOP62   NOP50; NOP11; NOP1;
#define NOP63   NOP50; NOP12; NOP1;
#define NOP64   NOP50; NOP13; NOP1;
#define NOP65   NOP50; NOP14; NOP1;
#define NOP66   NOP50; NOP15; NOP1;
#define NOP67   NOP50; NOP16; NOP1;
#define NOP68   NOP50; NOP17; NOP1;
#define NOP69   NOP50; NOP18; NOP1;
#define NOP70   NOP50; NOP19; NOP1;
#define NOP71   NOP50; NOP20; NOP1;
#define NOP72   NOP50; NOP21; NOP1;
#define NOP73   NOP50; NOP22; NOP1;
#define NOP74   NOP50; NOP23; NOP1;
#define NOP75   NOP50; NOP24; NOP1;
#define NOP76   NOP50; NOP25; NOP1;
#define NOP77   NOP50; NOP26; NOP1;
#define NOP78   NOP50; NOP27; NOP1;
#define NOP79   NOP50; NOP28; NOP1;
#define NOP80   NOP50; NOP29; NOP1;
#define NOP81   NOP50; NOP30; NOP1;
#define NOP82   NOP50; NOP31; NOP1;
#define NOP83   NOP50; NOP32; NOP1;
#define NOP84   NOP50; NOP33; NOP1;
#define NOP85   NOP50; NOP34; NOP1;
#define NOP86   NOP50; NOP35; NOP1;
#define NOP87   NOP50; NOP36; NOP1;
#define NOP88   NOP50; NOP37; NOP1;
#define NOP89   NOP50; NOP38; NOP1;
#define NOP90   NOP50; NOP39; NOP1;
#define NOP91   NOP50; NOP40; NOP1;
#define NOP92   NOP50; NOP41; NOP1;
#define NOP93   NOP50; NOP42; NOP1;
#define NOP94   NOP50; NOP43; NOP1;
#define NOP95   NOP50; NOP44; NOP1;
#define NOP96   NOP50; NOP45; NOP1;
#define NOP97   NOP50; NOP46; NOP1;
#define NOP98   NOP50; NOP47; NOP1;
#define NOP99   NOP50; NOP48; NOP1;
#define NOP100  NOP50; NOP50;

#define _NOP_DELAY(value)       __paste(NOP,value);


#if (CVD_CHOLD_CHARGE_DELAY - 2 - 3 * ((CVD_CHOLD_CHARGE_DELAY-2)/3)) == 1 
    #define CVD_DELAY_CHOLD_REMAINDER()   _NOP_DELAY(1);
#elif (CVD_CHOLD_CHARGE_DELAY - 2 - 3 * ((CVD_CHOLD_CHARGE_DELAY-2)/3)) == 2
    #define CVD_DELAY_CHOLD_REMAINDER()   _NOP_DELAY(2);
#else
    #define CVD_DELAY_CHOLD_REMAINDER()
#endif

#if defined(_12F615) || defined(_12HV615)
    #define CVD_DELAY_CHOLD()  _NOP_DELAY(CVD_CHOLD_CHARGE_DELAY);
#else
    #if CVD_CHOLD_CHARGE_DELAY > 4
        #define CVD_DELAY_VARIABLE_REQUIRED
        #define CVD_DELAY_CHOLD()                                           \
            do {                                                            \
                asm("BANKSEL    _mTouchCVD_delayCount"                  );  \
                asm("movlw  "   ___mkstr(CVD_CHOLD_CHARGE_DELAY-2)  "/3");  \
                asm("movwf      _mTouchCVD_delayCount"                  );  \
                asm("decfsz     _mTouchCVD_delayCount, F"               );  \
                asm("goto $-1");                                            \
                CVD_DELAY_CHOLD_REMAINDER();                                \
            } while(0)
    #else
        #define CVD_DELAY_CHOLD()   _NOP_DELAY(CVD_CHOLD_CHARGE_DELAY);
    #endif
#endif 

#if (CVD_SETTLING_DELAY - 2 - 3 * ((CVD_SETTLING_DELAY-2)/3)) == 1
    #define CVD_DELAY_SETTLE_REMAINDER()   _NOP_DELAY(1);
#elif (CVD_SETTLING_DELAY - 2 - 3 * ((CVD_SETTLING_DELAY-2)/3)) == 2
    #define CVD_DELAY_SETTLE_REMAINDER()   _NOP_DELAY(2);
#else
    #define CVD_DELAY_SETTLE_REMAINDER()
#endif

#if defined(_12F615) || defined(_12HV615)
    #define CVD_DELAY_SETTLE()  _NOP_DELAY(CVD_SETTLING_DELAY);
#else
    #if CVD_SETTLING_DELAY > 4
        #if !defined(CVD_DELAY_VARIABLE_REQUIRED)
            #define CVD_DELAY_VARIABLE_REQUIRED
        #endif
        
        #define CVD_DELAY_SETTLE()                                          \
            do {                                                            \
                asm("BANKSEL    _mTouchCVD_delayCount"                  );  \
                asm("movlw "    ___mkstr(CVD_SETTLING_DELAY-2)      "/3");  \
                asm("movwf      _mTouchCVD_delayCount"                  );  \
                asm("decfsz     _mTouchCVD_delayCount,F"                );  \
                asm("goto       $-1"                                    );  \
                CVD_DELAY_SETTLE_REMAINDER();                               \
            } while(0)
    #else
        #define CVD_DELAY_SETTLE()  _NOP_DELAY(CVD_SETTLING_DELAY);
    #endif       
#endif

#if (CVD_UNIMPLEMENTED_AVAILABLE == 1)
    #define CVD_GO_DONE_DELAY()     asm("movlw " ___mkstr(CVD_SELECT_ISO_NOGO | 0x02));  asm("movwf "  ___mkstr(MASKBANK(_ADCON0,CVD_ADCON0_BANK)));  
#else
    #if CVD_TAD == 1
        #if _XTAL_FREQ == 32000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(3);
        #elif _XTAL_FREQ == 16000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(1);
        #elif _XTAL_FREQ == 8000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #elif _XTAL_FREQ == 4000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #elif _XTAL_FREQ == 2000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #elif _XTAL_FREQ == 1000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #endif
    #elif CVD_TAD == 2
        #if _XTAL_FREQ == 32000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(7);
        #elif _XTAL_FREQ == 16000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(3);
        #elif _XTAL_FREQ == 8000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(1);
        #elif _XTAL_FREQ == 4000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #elif _XTAL_FREQ == 2000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #elif _XTAL_FREQ == 1000000
            #define CVD_GO_DONE_DELAY()     _NOP_DELAY(0);
        #endif
    #endif
#endif

#endif
/// @endcond
