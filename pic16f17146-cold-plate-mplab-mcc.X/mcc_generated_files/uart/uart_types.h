/**
 * UART Generated Driver Interface Header File
 * 
 * @file uart_types.h
 * 
 * @defgroup uart_types UART_TYPES
 * 
 * @brief This file contains APIs for UART module.
 *
 * @version UART Driver Version 3.0.0
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

#ifndef UART_TYPES_H
#define	UART_TYPES_H

/**
  Section: Included Files
*/
#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

   
/**
  Section: Data Type Definitions
*/ 
      
/**
@ingroup uartdriver
@enum UART_STANDARD_BAUDS
@brief This Enum can be used to set UART standard
baud-rates using \ref UARTx_BRGSet function e.g. \ref UART1_BRGSet.
*/
enum UART_STANDARD_BAUDS{
UART_110 = 0,
UART_300 = 1,
UART_600 = 2,
UART_1200 = 3,
UART_2400 = 4,
UART_4800 = 5,
UART_9600 = 6,
UART_14400 = 7,
UART_19200 = 8,
UART_38400 = 9,
UART_57600 = 10,
UART_115200 = 11,
UART_230400 = 12,
UART_460800 = 13,
UART_921600 = 14,
};


#ifdef	__cplusplus
}
#endif

#endif	/* UART_TYPES_H */

