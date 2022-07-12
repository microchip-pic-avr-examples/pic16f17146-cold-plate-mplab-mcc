/**
 * TMR2 Generated Driver API Header File
 *
 * @file tmr2.h
 *  
 * @defgroup tmr2 TMR2
 *
 * @brief This is the generated header file for the TMR2 module.
 *
 * @version TMR2 Driver Version 3.0.1
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

#ifndef TMR2_H
#define TMR2_H

/**
 * @brief This file contains API prototypes and other data types for TMR2 module.
 * @{
 */

#include <stdint.h>
#include <stdbool.h>
#include "timer_interface.h"

/**
 Section: Data Type Definitions
*/
/**
 @ingroup tmr2
 @struct TMR_INTERFACE
 @brief This is an instance of TMR_INTERFACE for TMR2 module
 */
extern const struct TMR_INTERFACE Timer2;

/**
 * @ingroup tmr2
 * @enum Timer2_HLT_EXT_RESET_SOURCE
 * @brief Defines the several modes of operation of the Timer with HLT extension.
 */

typedef enum
{

	/* Roll-over Pulse mode clears the TMRx upon TMRx = PRx, then continue running.
	ON bit must be set and is not affected by Resets
	*/

   /* Roll-over Pulse mode indicates that Timer starts
   immediately upon ON = 1 (Software Control)
   */
   Timer2_ROP_STARTS_TMRON,

   /* Roll-over Pulse mode indicates that the Timer starts
       when ON = 1 and TMRx_ers = 1. Stops when TMRx_ers = 0
     */
   Timer2_ROP_STARTS_TMRON_ERSHIGH,

   /* Roll-over Pulse mode indicates that the Timer starts
      when ON = 1 and TMRx_ers = 0. Stops when TMRx_ers = 1
     */
   Timer2_ROP_STARTS_TMRON_ERSLOW,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon rising or falling edge of TMRx_ers
     */
   Timer2_ROP_RESETS_ERSBOTHEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
    upon rising edge of TMRx_ers
     */
   Timer2_ROP_RESETS_ERSRISINGEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon falling edge of TMRx_ers
     */
   Timer2_ROP_RESETS_ERSFALLINGEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon TMRx_ers = 0
     */
   Timer2_ROP_RESETS_ERSLOW,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon TMRx_ers = 1
     */
   Timer2_ROP_RESETS_ERSHIGH,

    /*In all One-Shot mode the timer resets and the ON bit is
	cleared when the timer value matches the PRx period
	value. The ON bit must be set by software to start
	another timer cycle.
	*/

   /* One shot mode indicates that the Timer starts
    immediately upon ON = 1 (Software Control)
     */
   Timer2_OS_STARTS_TMRON,

   /* One shot mode indicates that the Timer starts
    when a rising edge is detected on the TMRx_ers
     */
   Timer2_OS_STARTS_ERSRISINGEDGE ,

   /* One shot mode indicates that the Timer starts
    when a falling edge is detected on the TMRx_ers
     */
   Timer2_OS_STARTS_ERSFALLINGEDGE ,

   /* One shot mode indicates that the Timer starts
    when either a rising or falling edge is detected on TMRx_ers
     */
   Timer2_OS_STARTS_ERSBOTHEDGE,

   /* One shot mode indicates that the Timer starts
    upon first TMRx_ers rising edge and resets on all
	subsequent TMRx_ers rising edges
     */
   Timer2_OS_STARTS_ERSFIRSTRISINGEDGE,

   /* One shot mode indicates that the Timer starts
    upon first TMRx_ers falling edge and restarts on all
	subsequent TMRx_ers falling edges
     */
   Timer2_OS_STARTS_ERSFIRSTFALLINGEDGE,

   /* One shot mode indicates that the Timer starts
    when a rising edge is detected on the TMRx_ers,
	resets upon TMRx_ers = 0
     */
   Timer2_OS_STARTS_ERSRISINGEDGEDETECT,
     /* One shot mode indicates that the Timer starts
    when a falling edge is detected on the TMRx_ers,
	resets upon TMRx_ers = 1
     */
   Timer2_OS_STARTS_ERSFALLINGEDGEDETECT,
   
   /* One shot mode indicates that the Timer starts
    when a TMRx_ers = 1,ON =1 and resets upon TMRx_ers =0
    */
   Timer2_OS_STARTS_TMRON_ERSHIGH = 0x16,
           
   /* One shot mode indicates that the Timer starts
     when a TMRx_ers = 0,ON = 1 and resets upon TMRx_ers =1 
    */
   Timer2_OS_STARTS_TMRON_ERSLOW = 0x17,
        
   /*In all Mono-Stable mode the ON bit must be initially set,but
     not cleared upon the TMRx = PRx, and the timer will start upon
     an TMRx_ers start event following TMRx = PRx.*/
               
   /* Mono Stable mode indicates that the Timer starts
      when a rising edge is detected on the TMRx_ers and ON = 1
    */
   Timer2_MS_STARTS_TMRON_ERSRISINGEDGEDETECT = 0x11,
           
   /* Mono Stable mode indicates that the Timer starts
      when a falling edge is detected on the TMRx_ers and ON = 1
    */
   Timer2_MS_STARTS_TMRON_ERSFALLINGEDGEDETECT = 0x12,
           
   /* Mono Stable mode indicates that the Timer starts
      when  either a rising or falling edge is detected on TMRx_ers 
      and ON = 1
    */
   Timer2_MS_STARTS_TMRON_ERSBOTHEDGE = 0x13
           
} Timer2_HLT_MODE;

/**
 * @ingroup tmr2
 * @enum Timer2_HLT_EXT_RESET_SOURCE
 * @brief Defines the different reset sources of the HLT.
 */
typedef enum
{
    /*
     * T2INPPS_PIN as the Timer external reset source
     */
    Timer2_T2INPPS_PIN =  0x0,   
    /*
     * TMR4_POSTSCALED as the Timer external reset source
     */
    Timer2_TMR4_POSTSCALED =  0x2,   
    /*
     * CCP1OUT as the Timer external reset source
     */
    Timer2_CCP1OUT =  0x4,   
    /*
     * CCP2OUT as the Timer external reset source
     */
    Timer2_CCP2OUT =  0x5,   
    /*
     * PWM1_OUT1 as the Timer external reset source
     */
    Timer2_PWM1_OUT1 =  0x6,   
    /*
     * PWM1_OUT2 as the Timer external reset source
     */
    Timer2_PWM1_OUT2 =  0x7,   
    /*
     * PWM2_OUT1 as the Timer external reset source
     */
    Timer2_PWM2_OUT1 =  0x8,   
    /*
     * PWM2_OUT2 as the Timer external reset source
     */
    Timer2_PWM2_OUT2 =  0x9,   
    /*
     * CMP1OUT as the Timer external reset source
     */
    Timer2_CMP1OUT =  0xe,   
    /*
     * CMP2OUT as the Timer external reset source
     */
    Timer2_CMP2OUT =  0xf,   
    /*
     * ZCDOUT as the Timer external reset source
     */
    Timer2_ZCDOUT =  0x10,   
    /*
     * CLC1OUT as the Timer external reset source
     */
    Timer2_CLC1OUT =  0x11,   
    /*
     * CLC2OUT as the Timer external reset source
     */
    Timer2_CLC2OUT =  0x12,   
    /*
     * CLC3OUT as the Timer external reset source
     */
    Timer2_CLC3OUT =  0x13,   
    /*
     * CLC4OUT as the Timer external reset source
     */
    Timer2_CLC4OUT =  0x14   
} Timer2_HLT_EXT_RESET_SOURCE;

/**
  Section: Macro Declarations
*/

/**
  Section: TMR2 APIs
*/

/**
 * @ingroup tmr2
 * @brief This API initializes the TMR2 module.
 *        This routine must be called before any other TMR2 routines.
 * @param none
 * @return none
 */
 void Timer2_Initialize(void);

/**
 * @ingroup tmr2
 * @brief Configures the Hardware Limit Timer mode.
 *        Writes the T2HLTbits.MODE bits.
 *        TMR2 should be initialized with Timer2_Initialize after calling this API.
 * @param mode - Value to write into T2HLTbits.MODE bits.
 * @return none
 */
void Timer2_ModeSet(Timer2_HLT_MODE mode);

/**
 * @ingroup tmr2
 * @brief Configures the HLT external reset source.
 *        Writes the T2RSTbits.RSEL bits.
 *        TMR2 should be initialized with Timer2_Initialize after calling this API.
 * @param reset - Value to write into T2RSTbits.RSEL bits.
 * @return none
 */
void Timer2_ExtResetSourceSet(Timer2_HLT_EXT_RESET_SOURCE reset);

/**
 * @ingroup tmr2
 * @brief This function starts TMR2.
 *        TMR2 should be initialized with Timer2_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer2_Start(void);

/**
 * @ingroup tmr2
 * @brief This function stops TMR2.
 *        TMR2 should be initialized with Timer2_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer2_Stop(void);

/**
 * @ingroup tmr2
 * @brief This function reads the 8 bits from TMR2 register.
 *        TMR2 should be initialized with Timer2_Initialize() before calling this API.
 * @param none.
 * @return 8-bit data from TMR2 register.
 */
uint8_t Timer2_Read(void);

/**
 * @ingroup tmr2
 * @brief This function writes 8-bit value to TMR2 register.
 *        TMR2 should be initialized with Timer2_Initialize() before calling this API.
 * @param 8-bit value to be written to TMR2 register.
 * @return none
 */
void Timer2_Write(uint8_t timerVal);

/**
 * @ingroup tmr2
 * @brief This function loads 8 bit value to PR2H register.
 *        TMR2 should be initialized with Timer2_Initialize() before calling this API.
 * @param 8-bit value to be written to PR2 register.
 * @return none
 */
void Timer2_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr2
 * @brief Setter function for TMR2 overflow Callback.
 * @param CallbackHandler - Pointer to custom Callback.
 * @return none
 */
void Timer2_OverflowCallbackRegister(void (* InterruptHandler)(void));

/**
 * @ingroup tmr2
 * @brief This function performs tasks to be executed on timer overflow event
 * @param none
 * @return none
 */
void Timer2_Tasks(void);

#endif // TMR2_H
/**
 End of File
*/
