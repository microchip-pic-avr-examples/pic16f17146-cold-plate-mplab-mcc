/**
 * Interrupt Manager Generated Driver API Header File
 * 
 * @file interrupt.h
 * 
 * @defgroup interrupt INTERRUPT
 * 
 * @brief This file contains API prototypes and other datatypes for Interrupt Manager.
 *
 * @version Interrupt Manager Driver Version 2.0.4
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

#ifndef INTERRUPT_H
#define INTERRUPT_H


/**
 * @ingroup interrupt
 * @brief This macro will enable global interrupts.
 * @param void
 * @return void
 */
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

/**
 * @ingroup interrupt
 * @brief This macro will disable global interrupts.
 * @param void
 * @return void
 */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

/**
 * @ingroup interrupt
 * @brief This macro will return the global interrupt enable bit status.
 * @param void
 * @retval 0 - Global Interrupt Disabled
 * @retval 1 - Global Interrupt Enabled
 */
#define INTERRUPT_GlobalInterruptStatus() (INTCONbits.GIE)

/**
 * @ingroup interrupt
 * @brief This macro will enable peripheral interrupts.
 * @param void
 * @return void
 */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

/**
 * @ingroup interrupt
 * @brief This macro will disable peripheral interrupts.
 * @param void
 * @return void
 */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

/**
 * @ingroup interrupt
 * @brief Initializes Peripheral Interrupt priorities; Enables/disables priority vectors; and, Initializes External Interrupt.
 * @param void
 * @return void
 */
void INTERRUPT_Initialize (void);


/**
 * @ingroup interrupt
 * @brief This routine clears the interrupt flag for the external interrupt, INT.
 * @param void
 * @return void
 */
#define EXT_INT_InterruptFlagClear()       (PIR0bits.INTF = 0)

/**
 * @ingroup interrupt
 * @brief This routine clears the interrupt enable for the external interrupt, INT, and thereafter external interrupts on this pin will not be serviced by the interrupt handler.
 * @param void
 * @return void
 */
#define EXT_INT_InterruptDisable()     (PIE0bits.INTE = 0)

/**
 * @ingroup interrupt
 * @brief This routine sets the interrupt enable for the external interrupt, INT, and thereafter external interrupts on this pin will be serviced by the interrupt handler.
 * @param void
 * @return void
 */
#define EXT_INT_InterruptEnable()       (PIE0bits.INTE = 1)

/**
 * @ingroup interrupt
 * @brief This routine set the edge detect of the extern interrupt to positive edge, and thereafter interrupt flag will be set when the external interrupt pins level transitions from a low to high level.
 * @param void
 * @return void
 */
#define EXT_INT_risingEdgeSet()          (INTCONbits.INTEDG = 1)

/**
 * @ingroup interrupt
 * @brief This routine set the edge detect of the extern interrupt to negative edge, and thereafter interrupt flag will be set when the external interrupt pins level transitions from a high to low level.
 * @param void
 * @return void
 */
#define EXT_INT_fallingEdgeSet()          (INTCONbits.INTEDG = 0)

/**
   Section: External Interrupt Handlers
 */

/**
 * @ingroup interrupt
 * @brief This ISR will execute whenever the signal on the INT pin will transition to the preconfigured state.
 * @pre Interrupt Manager is initialized.
 * @param void
 * @return void
 */
void INT_ISR(void);

/**
 * @ingroup interrupt
 * @brief Allows for a specific callback function to be called in the INT ISR and allows for a non-specific interrupt handler to be called at runtime.
 * @pre Interrupt Manager is initialized.
 * @param void
 * @return void
 */
void INT_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Allows selecting an interrupt handler for EXT_INT - INT at application runtime.
 * @pre Interrupt Manager is initialized.
 * @param (*InterruptHandler)(void) - InterruptHandler function pointer
 * @return void
 */
void INT_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief This is the dynamic interrupt handler which is called every time the INT ISR is executed and allows any function to be registered at runtime.
 * @pre Interrupt Manager is initialized.
 * @param void
 * @return void
 */
extern void (*INT_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief This is the default interrupt handler which is called every time the INT ISR is executed and allows any function to be registered at runtime.
 * @pre Interrupt Manager is initialized.
 * @param void
 * @return void
 */
void INT_DefaultInterruptHandler(void);

#endif  // INTERRUPT_H
/**
 End of File
*/