/**
 * I2C Generated Driver Interface Header File
 *
 * @file i2c_host_interface.h
 *
 * @defgroup i2c_host_interface I2C_HOST_INTERFACE
 *
 * @brief This file contains other data types for I2C module.
 *
 * @version I2C Driver Version 2.1.0
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

#ifndef I2C_HOST_INTERFACE_H
#define I2C_HOST_INTERFACE_H

/**
  Section: Included Files
 */
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
#include "i2c_host_types.h"

/**
 * @ingroup i2c_host_interface
 * @strcut i2c_host_interface_t
 * @brief Structure containing the function pointers of I2C drivers.
 */
typedef struct
{
    void (*Initialize)(void);
    void (*Deinitialize)(void);
    bool (*Write)(uint16_t address, uint8_t *data, size_t dataLength);
    bool (*Read)(uint16_t address, uint8_t *data, size_t dataLength);
    bool (*WriteRead)(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength);
    bool (*TransferSetup)(i2c_host_transfer_setup_t* setup, uint32_t srcClkFreq);
    i2c_host_error_t (*ErrorGet)(void);
    bool (*IsBusy)(void);
    void (*CallbackRegister)(void (*callback)(void));
    void (*Tasks)(void);
} i2c_host_interface_t;

#endif // end of I2C_HOST_INTERFACE_H

