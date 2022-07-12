/**
 * System Driver Header File
 * 
 * @file system.h
 * 
 * @defgroup systemdriver System Driver
 * 
 * @brief This is the generated header file for the System Driver.
 *
 * @version Driver Version 2.0.1
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

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

#ifndef SYSTEM_H
#define	SYSTEM_H

/**
  Section: Included Files
*/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include "config_bits.h"
#include "../system/clock.h"
#include "../system/pins.h"
#include "../adcc/adcc.h"
#include "../clc/clc1.h"
#include "../clc/clc2.h"
#include "../comparator/cmp1.h"
#include "../dac/dac1.h"
#include "../uart/eusart1.h"
#include "../pwm/pwm2_16bit.h"
#include "../pwm/pwm1_16bit.h"
#include "../i2c_host/mssp1.h"
#include "../opa/opa1.h"
#include "../timer/tmr0.h"
#include "../timer/tmr1.h"
#include "../timer/tmr2.h"
#include "../timer/tmr3.h"
#include "../timer/tmr4.h"
#include "../system/interrupt.h"

/**
 * @ingroup systemdriver
 * @brief This initializes the system module and must be called before any other API is called.
 * This routine should only be called once during system initialization.
 * @param None
 * @return None
*/
void SYSTEM_Initialize(void);

#endif //SYSTEM_H
