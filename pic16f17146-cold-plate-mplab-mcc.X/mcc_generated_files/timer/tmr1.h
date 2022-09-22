/**
 * TMR1 Generated Driver API Header File
 *
 * @file tmr1.h
 *
 * @defgroup tmr1 TMR1
 *
 * @brief API prototypes and other datatypes for the TMR1 module.
 *
 * @version TMR1 Driver Version 3.0.1
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

#ifndef TMR1_H
#define TMR1_H

#include <stdbool.h>
#include <stdint.h>
#include "timer_interface.h"


/**
 * @ingroup tmr1
 * @struct TMR_INTERFACE
 * @brief This is an instance of TMR_INTERFACE for Timer module
 */
extern const struct TMR_INTERFACE Timer1;

/**
 * @ingroup tmr1
 * @brief Initializes the timer module.
 *        This routine must be called before any other Timer routines.
 * @param none
 * @return none
 */
void Timer1_Initialize(void);

/**
 * @ingroup tmr1
 * @brief Starts the timer.
 * @pre Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer1_Start(void);

/**
 * @ingroup tmr1
 * @brief Stops the timer.
 * @pre Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer1_Stop(void);

/**
 * @ingroup tmr1
 * @brief Reads the 16-bits from TMR1 register.
 *        Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param none
 * @return uint16_t - 16-bit data from TMR1 register.
 */
uint16_t Timer1_Read(void);

/**
 * @ingroup tmr1
 * @brief Writes 16-bit value to TMR1 register.
 * @pre Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param size_t timerVal - 16-bit value to be written to TMR1 register.
 * @return none
 */
void Timer1_Write(size_t timerVal);

/**
 * @ingroup tmr1
 * @brief Loads 8 bit value to TMR1 register.
 * @pre Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer1_Reload(void);


/**
 * @ingroup tmr1
 * @brief Starts the single pulse acquisition in TMR1 gate operation.
 * @Pre This function must be used when the TMR1 gate is enabled.
 * @param none
 * @return none
 */
void Timer1_StartSinglePulseAcquisition(void);

/**
 * @ingroup tmr1
 * @brief Reads the TMR1 gate value and returns it.
 * @pre This function must be used when the TMR1 gate is enabled.
 * @param none
 * @return uint8_t - Gate value status.
 */
uint8_t Timer1_CheckGateValueStatus(void);


/**
 * @ingroup tmr1
 * @brief Setter function for Timer overflow callback.
 * @param void (* CallbackHandler)(void) - Pointer to custom Callback.
 * @return none
 */
 void Timer1_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr1
 * @brief Performs tasks to be executed on timer overflow event
 * @param none
 * @return none
 */
void Timer1_Tasks(void);

/**
 * @ingroup tmr1
 * @brief Checks for the timer overflow flag when in polling mode.
 * @param none
 * @retval true  - timer overflow has occured.
 * @retval false - timer overflow has not occured.
 */
bool Timer1_HasOverflowOccured(void);


/**
 * @ingroup tmr1
 * @brief Timer Gate Interrupt Service Routine (ISR) called by the Interrupt Manager.
 * @param none
 * @return none
 */
void Timer1_GateISR(void);

#endif // TMR1_H