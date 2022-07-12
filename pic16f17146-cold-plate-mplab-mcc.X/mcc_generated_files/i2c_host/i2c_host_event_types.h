/**
 * I2C Generated Driver Event Header File
 *
 * @file i2c_host_event_types.h
 *
 * @defgroup i2c_host_events I2C_HOST_EVENTS
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

#ifndef I2C_EVENT_TYPES_H
#define	I2C_EVENT_TYPES_H

#include "i2c_host_types.h"

/**
 * @ingroup i2c_host_events
 * @enum i2c_host_event_states_t
 * @brief I2C event states
 */
typedef enum
{
    I2C_STATE_IDLE = 0,     /**< Idle state*/
    I2C_STATE_SEND_RD_ADDR, /**< Send read address state*/
    I2C_STATE_SEND_WR_ADDR, /**< Send write address state */
    I2C_STATE_TX,           /**< Transmit data state*/
    I2C_STATE_RX,           /**< Receive data state*/
    I2C_STATE_NACK,         /**< Nack state*/
    I2C_STATE_ERROR,        /**< Error state*/
    I2C_STATE_STOP,         /**< Stop state*/
    I2C_STATE_RESET         /**< Reset state*/
} i2c_host_event_states_t; 

/**
 * @ingroup i2c_host_events
 * @struct i2c_host_event_status_t
 * @brief I2C Event Status Structure
 */
typedef struct
{
    bool busy; /**< Software busy flag*/
    uint16_t address; /**< Pointer to write buffer*/
    uint8_t *writePtr; /**< Pointer to write buffer*/
    size_t writeLength; /**< Write buffer length*/
    uint8_t *readPtr; /**< Pointer to read buffer*/
    size_t readLength; /**< Read buffer length*/
    bool switchToRead; /**< Switch i2c write to read mode*/
    i2c_host_error_t errorState; /**< Error State*/
    i2c_host_event_states_t state;  /**< Event State index*/
} i2c_host_event_status_t;

#endif /* end of I2C_EVENT_TYPES_H */