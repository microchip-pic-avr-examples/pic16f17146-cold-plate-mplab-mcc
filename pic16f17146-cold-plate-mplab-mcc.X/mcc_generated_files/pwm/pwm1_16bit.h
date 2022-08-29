/**
 * PWM1_16BIT Generated Driver API Header File
 *
 * @file pwm1_16bit.h
 *
 * defgroup pwm1_16bit PWM1_16BIT
 *
 * @brief This header file provides APIs for the PWM1_16BIT driver.
 *
 * @version PWM1_16BIT Driver Version <!--Use existing driver version-->
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

#ifndef PWM1_16BIT_H
#define PWM1_16BIT_H

/**
 * @section: Included Files
 */

#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup pwm1_16bit
 * @brief Initializes the PWM1_16BIT module
 *        This routine must be called before any other PWM1_16BIT routine
 * @param none
 * @return none
 */
void FET_PWM_Initialize(void);

/**
 * @ingroup pwm1_16bit
 * @brief Enables the PWM1_16BIT module
 * @param none
 * @return none
 */
void FET_PWM_Enable(void);

/**
 * @ingroup pwm1_16bit
 * @brief Disables the PWM1_16BIT module
 *        In case if one wants to re-initialize PWM1_16BIT, this function
 *        must be called before FET_PWM_Initialize()
 * @param none
 * @return none
 */
void FET_PWM_Disable(void);

/**
 * @ingroup pwm1_16bit
 * @brief This routine configures the total PWM1_16BIT period. 
 *        FET_PWM_LoadBufferRegisters() must be called after this API
 * @param [in] uint16_t periodCount - Desired 16-bit PWM1_16BIT period
 * @return none.
 */
void FET_PWM_WritePeriodRegister(uint16_t periodCount);

/**
 * @ingroup pwm1_16bit
 * @brief This routine configures the active period or duty cycle of
 *        slice-1, parameter 1 output. FET_PWM_LoadBufferRegisters() must
 *        be called after this API
 * @param [in] uint16_t value - PWMPWM1_16BITS1P1 register value
 * @return none
 */
void FET_PWM_SetSlice1Output1DutyCycleRegister(uint16_t value);

/**
 * @ingroup pwm1_16bit
 * @brief This routine configures the active period or duty cycle of
 *        slice-1, parameter 2 output. FET_PWM_LoadBufferRegisters() must
 *        be called after this API
 * @param [in] uint16_t value - PWMPWM1_16BITS1P2 register value
 * @return none
 */
void FET_PWM_SetSlice1Output2DutyCycleRegister(uint16_t value);

/**
 * @ingroup pwm1_16bit
 * @brief This routine is used to load period or duty cycle registers on the next period event
 *        This API must be called after changing PR/P1/P2 registers
 * @param none
 * @return none
 */
void FET_PWM_LoadBufferRegisters(void);

/**
 * @ingroup pwm1_16bit
 * @brief Interrupt handler for PWM1_16BIT outputs
 * @param none
 * @return none
 */
void FET_PWM_PWMI_ISR(void);

/**
 * @ingroup pwm1_16bit
 * @brief Interrupt handler for PWM1_16BIT period
 * @param none
 * @return none
 */
void FET_PWM_PWMPI_ISR(void);

/**
 * @ingroup pwm1_16bit
 * @brief Setter for slice 1, parameter 1 out interrupt handler
 * @param void (* InterruptHandler)(void) - Pointer to set interrupt handler
 * @return none
 */
void FET_PWM_Slice1Output1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup pwm1_16bit
 * @brief Setter for slice 1, parameter 2 out interrupt handler
 * @param void (* InterruptHandler)(void) - Pointer to set interrupt handler
 * @return none
 */
void FET_PWM_Slice1Output2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup pwm1_16bit
 * @brief Setter for PWM1_16BIT period interrupt handler
 * @param void (* InterruptHandler)(void) - Pointer to set interrupt handler
 * @return none
 */
void FET_PWM_Period_SetInterruptHandler(void (* InterruptHandler)(void));

#endif //PWM1_16BIT_H
