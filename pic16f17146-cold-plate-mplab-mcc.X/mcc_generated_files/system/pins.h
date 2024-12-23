/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
� [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define LED_ERROR_TRIS                 TRISAbits.TRISA0
#define LED_ERROR_LAT                  LATAbits.LATA0
#define LED_ERROR_PORT                 PORTAbits.RA0
#define LED_ERROR_WPU                  WPUAbits.WPUA0
#define LED_ERROR_OD                   ODCONAbits.ODCA0
#define LED_ERROR_ANS                  ANSELAbits.ANSA0
#define LED_ERROR_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_ERROR_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_ERROR_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_ERROR_GetValue()           PORTAbits.RA0
#define LED_ERROR_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_ERROR_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_ERROR_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define LED_ERROR_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define LED_ERROR_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define LED_ERROR_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define LED_ERROR_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define LED_ERROR_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set IO_RA1 aliases
#define LED_STATUS_TRIS                 TRISAbits.TRISA1
#define LED_STATUS_LAT                  LATAbits.LATA1
#define LED_STATUS_PORT                 PORTAbits.RA1
#define LED_STATUS_WPU                  WPUAbits.WPUA1
#define LED_STATUS_OD                   ODCONAbits.ODCA1
#define LED_STATUS_ANS                  ANSELAbits.ANSA1
#define LED_STATUS_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_STATUS_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_STATUS_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_STATUS_GetValue()           PORTAbits.RA1
#define LED_STATUS_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_STATUS_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_STATUS_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define LED_STATUS_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define LED_STATUS_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define LED_STATUS_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define LED_STATUS_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED_STATUS_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set IO_RA2 aliases
#define NTC_COLD_SENSE_IN_TRIS                 TRISAbits.TRISA2
#define NTC_COLD_SENSE_IN_LAT                  LATAbits.LATA2
#define NTC_COLD_SENSE_IN_PORT                 PORTAbits.RA2
#define NTC_COLD_SENSE_IN_WPU                  WPUAbits.WPUA2
#define NTC_COLD_SENSE_IN_OD                   ODCONAbits.ODCA2
#define NTC_COLD_SENSE_IN_ANS                  ANSELAbits.ANSA2
#define NTC_COLD_SENSE_IN_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define NTC_COLD_SENSE_IN_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define NTC_COLD_SENSE_IN_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define NTC_COLD_SENSE_IN_GetValue()           PORTAbits.RA2
#define NTC_COLD_SENSE_IN_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define NTC_COLD_SENSE_IN_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define NTC_COLD_SENSE_IN_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define NTC_COLD_SENSE_IN_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define NTC_COLD_SENSE_IN_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define NTC_COLD_SENSE_IN_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define NTC_COLD_SENSE_IN_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define NTC_COLD_SENSE_IN_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_RA4 aliases
#define FAN1_SPD_TRIS                 TRISAbits.TRISA4
#define FAN1_SPD_LAT                  LATAbits.LATA4
#define FAN1_SPD_PORT                 PORTAbits.RA4
#define FAN1_SPD_WPU                  WPUAbits.WPUA4
#define FAN1_SPD_OD                   ODCONAbits.ODCA4
#define FAN1_SPD_ANS                  ANSELAbits.ANSA4
#define FAN1_SPD_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define FAN1_SPD_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define FAN1_SPD_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define FAN1_SPD_GetValue()           PORTAbits.RA4
#define FAN1_SPD_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define FAN1_SPD_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define FAN1_SPD_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define FAN1_SPD_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define FAN1_SPD_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define FAN1_SPD_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define FAN1_SPD_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define FAN1_SPD_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set IO_RA5 aliases
#define FAN2_SPD_TRIS                 TRISAbits.TRISA5
#define FAN2_SPD_LAT                  LATAbits.LATA5
#define FAN2_SPD_PORT                 PORTAbits.RA5
#define FAN2_SPD_WPU                  WPUAbits.WPUA5
#define FAN2_SPD_OD                   ODCONAbits.ODCA5
#define FAN2_SPD_ANS                  ANSELAbits.ANSA5
#define FAN2_SPD_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define FAN2_SPD_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define FAN2_SPD_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define FAN2_SPD_GetValue()           PORTAbits.RA5
#define FAN2_SPD_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define FAN2_SPD_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define FAN2_SPD_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define FAN2_SPD_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define FAN2_SPD_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define FAN2_SPD_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define FAN2_SPD_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define FAN2_SPD_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_WPU                  WPUBbits.WPUB4
#define IO_RB4_OD                   ODCONBbits.ODCB4
#define IO_RB4_ANS                  ANSELBbits.ANSB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IO_RB5 aliases
#define RB5_IN0_TRIS                 TRISBbits.TRISB5
#define RB5_IN0_LAT                  LATBbits.LATB5
#define RB5_IN0_PORT                 PORTBbits.RB5
#define RB5_IN0_WPU                  WPUBbits.WPUB5
#define RB5_IN0_OD                   ODCONBbits.ODCB5
#define RB5_IN0_ANS                  ANSELBbits.ANSB5
#define RB5_IN0_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_IN0_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_IN0_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_IN0_GetValue()           PORTBbits.RB5
#define RB5_IN0_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_IN0_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_IN0_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_IN0_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_IN0_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define RB5_IN0_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define RB5_IN0_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_IN0_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set IO_RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_WPU                  WPUBbits.WPUB6
#define IO_RB6_OD                   ODCONBbits.ODCB6
#define IO_RB6_ANS                  ANSELBbits.ANSB6
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_RB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_RB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_RB6_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define IO_RB6_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set IO_RC0 aliases
#define NTC_HOT_SENSE_IN_TRIS                 TRISCbits.TRISC0
#define NTC_HOT_SENSE_IN_LAT                  LATCbits.LATC0
#define NTC_HOT_SENSE_IN_PORT                 PORTCbits.RC0
#define NTC_HOT_SENSE_IN_WPU                  WPUCbits.WPUC0
#define NTC_HOT_SENSE_IN_OD                   ODCONCbits.ODCC0
#define NTC_HOT_SENSE_IN_ANS                  ANSELCbits.ANSC0
#define NTC_HOT_SENSE_IN_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define NTC_HOT_SENSE_IN_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define NTC_HOT_SENSE_IN_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define NTC_HOT_SENSE_IN_GetValue()           PORTCbits.RC0
#define NTC_HOT_SENSE_IN_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define NTC_HOT_SENSE_IN_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define NTC_HOT_SENSE_IN_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define NTC_HOT_SENSE_IN_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define NTC_HOT_SENSE_IN_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define NTC_HOT_SENSE_IN_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define NTC_HOT_SENSE_IN_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define NTC_HOT_SENSE_IN_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set IO_RC1 aliases
#define BUTTON_TRIS                 TRISCbits.TRISC1
#define BUTTON_LAT                  LATCbits.LATC1
#define BUTTON_PORT                 PORTCbits.RC1
#define BUTTON_WPU                  WPUCbits.WPUC1
#define BUTTON_OD                   ODCONCbits.ODCC1
#define BUTTON_ANS                  ANSELCbits.ANSC1
#define BUTTON_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define BUTTON_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define BUTTON_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define BUTTON_GetValue()           PORTCbits.RC1
#define BUTTON_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define BUTTON_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define BUTTON_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define BUTTON_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define BUTTON_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define BUTTON_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define BUTTON_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define BUTTON_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_RC2_TRIS                 TRISCbits.TRISC2
#define IO_RC2_LAT                  LATCbits.LATC2
#define IO_RC2_PORT                 PORTCbits.RC2
#define IO_RC2_WPU                  WPUCbits.WPUC2
#define IO_RC2_OD                   ODCONCbits.ODCC2
#define IO_RC2_ANS                  ANSELCbits.ANSC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_RC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_RC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_RC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_RC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_RC2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_RC4 aliases
#define FAN_SPEED_TRIS                 TRISCbits.TRISC4
#define FAN_SPEED_LAT                  LATCbits.LATC4
#define FAN_SPEED_PORT                 PORTCbits.RC4
#define FAN_SPEED_WPU                  WPUCbits.WPUC4
#define FAN_SPEED_OD                   ODCONCbits.ODCC4
#define FAN_SPEED_ANS                  ANSELCbits.ANSC4
#define FAN_SPEED_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define FAN_SPEED_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define FAN_SPEED_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define FAN_SPEED_GetValue()           PORTCbits.RC4
#define FAN_SPEED_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define FAN_SPEED_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define FAN_SPEED_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define FAN_SPEED_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define FAN_SPEED_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define FAN_SPEED_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define FAN_SPEED_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define FAN_SPEED_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set IO_RC5 aliases
#define FET_CONTROL_TRIS                 TRISCbits.TRISC5
#define FET_CONTROL_LAT                  LATCbits.LATC5
#define FET_CONTROL_PORT                 PORTCbits.RC5
#define FET_CONTROL_WPU                  WPUCbits.WPUC5
#define FET_CONTROL_OD                   ODCONCbits.ODCC5
#define FET_CONTROL_ANS                  ANSELCbits.ANSC5
#define FET_CONTROL_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define FET_CONTROL_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define FET_CONTROL_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define FET_CONTROL_GetValue()           PORTCbits.RC5
#define FET_CONTROL_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define FET_CONTROL_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define FET_CONTROL_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define FET_CONTROL_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define FET_CONTROL_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define FET_CONTROL_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define FET_CONTROL_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define FET_CONTROL_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set IO_RC6 aliases
#define IO_RC6_TRIS                 TRISCbits.TRISC6
#define IO_RC6_LAT                  LATCbits.LATC6
#define IO_RC6_PORT                 PORTCbits.RC6
#define IO_RC6_WPU                  WPUCbits.WPUC6
#define IO_RC6_OD                   ODCONCbits.ODCC6
#define IO_RC6_ANS                  ANSELCbits.ANSC6
#define IO_RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_RC6_GetValue()           PORTCbits.RC6
#define IO_RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_RC6_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define IO_RC6_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define IO_RC6_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define IO_RC6_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define IO_RC6_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define IO_RC6_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/