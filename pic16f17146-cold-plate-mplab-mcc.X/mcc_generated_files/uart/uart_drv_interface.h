/**
 * UART Generated Driver Interface Header File
 * 
 * @file uart_drv_interface.h
 * 
 * @defgroup uart_drv_interface UART_DRV_INTERFACE
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

#ifndef UART_DRV_INTERFACE_H
#define	UART_DRV_INTERFACE_H

/**
  Section: Included Files
*/
#include <stdbool.h>
#include <stdint.h>
#include "uart_types.h"

#ifdef	__cplusplus
extern "C" {
#endif

   
/**
  Section: Data Type Definitions
*/ 
      
/**
 @ingroup UART
 @struct uart_drv_interface_t
 @brief Structure containing the function pointers of UART driver.
*/
typedef struct {
void (*Initialize)(void);   
void (*Deinitialize)(void);
uint8_t (*Read)(void);
void (*Write)(uint8_t);
bool (*IsRxReady)(void);
bool (*IsTxReady)(void);
bool (*IsTxDone)(void);
void (*TransmitEnable)(void);
void (*TransmitDisable)(void);
void (*AutoBaudSet)(bool enable);
bool (*AutoBaudQuery)(void);
bool (*AutoBaudEventEnableGet)(void);
void (*BRGCountSet)(uint32_t brgValue);
uint32_t (*BRGCountGet)(void);
void (*BaudRateSet)(uint32_t baudRate);
uint32_t (*BaudRateGet)(void);
size_t (*ErrorGet)(void);
void (*TxCompleteCallbackRegister)(void (*CallbackHandler) (void));
void (*RxCompleteCallbackRegister)(void (*CallbackHandler) (void));
void (*TxCollisionCallbackRegister)(void (*CallbackHandler) (void));
void (*FramingErrorCallbackRegister)(void (*CallbackHandler) (void));
void (*OverrunErrorCallbackRegister)(void (*CallbackHandler) (void));
void (*ParityErrorCallbackRegister)(void (*CallbackHandler) (void));
void (*EventCallbackRegister)(void (*CallbackHandler) (void));
}uart_drv_interface_t;


#ifdef	__cplusplus
}
#endif

#endif	/* UART_DRV_INTERFACE_H */

