/**
 * EUSART1 Generated Driver API Header File
 * 
 * @file eusart1.h
 * 
 * @defgroup eusart1 EUSART1
 * 
 * @brief This file contains API prototypes and other datatypes for EUSART1 module.
 *
 * @version EUSART1 Driver Version 3.0.0
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

#ifndef EUSART1_H
#define EUSART1_H

/**
  Section: Included Files
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../system/system.h"
#include "uart_drv_interface.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


#define UART1_interface UART1


#define UART1_Initialize     EUSART1_Initialize
#define UART1_Deinitialize   EUSART1_Deinitialize
#define UART1_Write          EUSART1_Write
#define UART1_Read           EUSART1_Read
#define UART1__IsRxReady     EUSART1_IsRxReady
#define UART1_IsTxReady      EUSART1_IsTxReady
#define UART1_IsTxDone       EUSART1_IsTxDone

#define UART1_TransmitEnable       EUSART1_TransmitEnable
#define UART1_TransmitDisable      EUSART1_TransmitDisable
#define UART1_AutoBaudSet          (NULL)
#define UART1_AutoBaudQuery        (NULL)
#define UART1_BRGCountSet                (NULL)
#define UART1_BRGCountGet                (NULL)
#define UART1_BaudRateSet                (NULL)
#define UART1_BaudRateGet                (NULL)
#define UART1__AutoBaudEventEnableGet    (NULL)
#define UART1_ErrorGet             EUSART1_ErrorGet

#define UART1_TxCompleteCallbackRegister     (NULL)
#define UART1_RxCompleteCallbackRegister      (NULL)
#define UART1_TxCollisionCallbackRegister  (NULL)
#define UART1_FramingErrorCallbackRegister EUSART1_FramingErrorCallbackRegister
#define UART1_OverrunErrorCallbackRegister EUSART1_OverrunErrorCallbackRegister
#define UART1_ParityErrorCallbackRegister  (NULL)
#define UART1_EventCallbackRegister        (NULL)


/**
 @ingroup eusart1
 @struct eusart1_status_t
 @breif This is a structre defined for errors in reception of data.
 */
typedef union {
    struct {
        uint8_t perr : 1;     /**<This is a bit field for Parity Error status*/
        uint8_t ferr : 1;     /**<This is a bit field for Framing Error status*/
        uint8_t oerr : 1;     /**<This is a bit field for Overfrun Error status*/
        uint8_t reserved : 5; /**<Reserved*/
    };
    size_t status;            /**<Group byte for status errors*/
}eusart1_status_t;



/**
 Section: Data Type Definitions
 */

/**
 * @ingroup eusart1
 * @brief External object for eusart1_interface.
 */
extern const uart_drv_interface_t UART1;

/**
 * @ingroup eusart1
 * @brief This API initializes the EUSART1 driver.
 *        This routine initializes the EUSART1 module.
 *        This routine must be called before any other EUSART1 routine is called.
 *        This routine should only be called once during system initialization.
 * @param None.
 * @return None.
 */
void EUSART1_Initialize(void);

/**
 * @ingroup eusart1
 * @brief This API Deinitializes the EUSART1 driver.
 *        This routine disables the EUSART1 module.
 * @param None.
 * @return None.
 */
void EUSART1_Deinitialize(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 module.     
 * @param None.
 * @return None.
 */
inline void EUSART1_Enable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 module.
 * @param None.
 * @return None.
 */
inline void EUSART1_Disable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 transmitter.
 *        EUSART1 should also be enable to send bytes over TX pin.
 * @param None.
 * @return None.
 */
inline void EUSART1_TransmitEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 transmitter.
 * @param None.
 * @return None.
 */
inline void EUSART1_TransmitDisable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 Receiver.
 *        EUSART1 should also be enable to receive bytes over RX pin.
 * @param None.
 * @return None.
 */
inline void EUSART1_ReceiveEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 Receiver.
 * @param None.
 * @return None.
 */
inline void EUSART1_ReceiveDisable(void);


/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 send break control.
 * @param None.
 * @return None.
 */
inline void EUSART1_SendBreakControlEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 send break control.
 * @param None.
 * @return None.
 */
inline void EUSART1_SendBreakControlDisable(void);

/**
 * @ingroup eusart1
 * @brief This API checks if EUSART1 receiver has received data and ready to be read.
 * @param None.
 * @retval true if EUSART1 receiver FIFO has a data
 * @retval false EUSART1 receiver FIFO is empty
 */
bool EUSART1_IsRxReady(void);

/**
 * @ingroup eusart1
 * @brief This function checks if EUSART1 transmitter is ready to accept a data byte.
 * @param None.
 * @retval true if EUSART1 transmitter FIFO has atleast 1 byte space
 * @retval false if EUSART1 transmitter FIFO is full
 */
bool EUSART1_IsTxReady(void);

/**
 * @ingroup eusart1
 * @brief This function return the status of transmit shift register (TSR).
 * @param None.
 * @retval true if Data completely shifted out from the TSR
 * @retval false if Data is present in Transmit FIFO and/or in TSR
 */
bool EUSART1_IsTxDone(void);

/**
 * @ingroup eusart1
 * @brief This function gets the error status of the last read byte.
 * @param None.
 * @return Status of the last read byte. See eusart1_status_t struct for more details.
 */
size_t EUSART1_ErrorGet(void);

/**
 * @ingroup eusart1
 * @brief This function reads the 8 bits from receiver FIFO register.
 * @pre The transfer status should be checked to see if the receiver is not empty
 *      before calling this function. EUSART1_IsRxReady() should be checked in if () before calling this API.
 * @param None.
 * @return 8-bit data from RX FIFO register.
 */
uint8_t EUSART1_Read(void);

/**
 * @ingroup eusart1
 * @brief This function writes a byte of data to the transmitter FIFO register.
 * @pre The transfer status should be checked to see if the transmitter is ready to accept a byte
 *      before calling this function. EUSART1_IsTxReady() should be checked in if() before calling this API.
 * @param txData  - Data byte to write to the TX FIFO.
 * @return None.
 */
void EUSART1_Write(uint8_t txData);

/**
 * @ingroup eusart1
 * @brief This API registers the function to be called upon framing error.
 * @param callbackHandler - a function pointer which will be called upon framing error condition.
 * @return None.
 */
void EUSART1_FramingErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup eusart1
 * @brief This API registers the function to be called upon overrun error.
 * @param callbackHandler - a function pointer which will be called upon overrun error condition.
 * @return None.
 */
void EUSART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void));

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // EUSART1_H
