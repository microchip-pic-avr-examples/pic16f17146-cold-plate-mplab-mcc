/**
 * DAC1 Generated Driver API Header File
 * 
 * @file dac1.h
 * 
 * @defgroup  dac1 DAC1
 * 
 * @brief This is the generated header file for the DAC1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 *
 * @version DAC1 Driver Version 2.1.0
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

#ifndef DAC1_H
#define DAC1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

/**
  Section: DAC1 APIs
*/

/**
 * @ingroup dac1
 * @brief  This routine initializes the DAC1 and must be called only once, before any other DAC1 routine is called.
 * @param void
 * @return void
 */ 
void DAC1_Initialize(void);

/**
 * @ingroup dac1
 * @brief  This routine pass the digital input data intoDAC1 voltage reference control register.
 * @param inputData - 8bit digital data to DAC1.
 * @return void
 */
void DAC1_SetOutput(uint8_t inputData);

/**
 * @ingroup dac1
 * @brief  This routine reads the digital input data fed to DAC1 voltage reference control register.
 * @param void
 * @return uint8_t inputData - digital data fed to DAC1
 */
uint8_t DAC1_GetOutput(void);

#endif // DAC1_H
/**
 End of File
*/

