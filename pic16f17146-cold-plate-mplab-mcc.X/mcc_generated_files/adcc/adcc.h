/**
 * ADCC Generated Driver API Header File
 * 
 * @file adcc.h
 * 
 * @defgroup  adcc ADCC
 * 
 * @brief This is the generated header file for the ADCC driver.
 *
 * @version ADCC Driver Version 1.0.1
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

#ifndef ADCC_H
#define ADCC_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

/**
 @ingroup adcc
 @typedef adc_result_t
 @brief This typedef should be used for result of A/D conversion.
*/
typedef uint16_t adc_result_t;
#ifndef uint24_t
typedef __uint24 uint24_t;
#endif


/**
 * @ingroup adcc
 * @enum adcc_channel_t
 * @brief This enumeration contains available ADC channels.
*/
typedef enum
{
    channel_ADCG1 =  0x3,
    channel_OPA1OUT =  0x39,
    channel_VSS =  0x3a,
    channel_Temp =  0x3b,
    channel_DAC1OUT =  0x3c,
    channel_DAC2OUT =  0x3d,
    channel_FVR_Buffer1 =  0x3e,
    channel_FVR_Buffer2 =  0x3f
} adcc_channel_t;

/**
  Section: ADCC Module APIs
*/

/**
 * @ingroup adcc
 * @brief This API initializes the ADC module. This routine must be called before any other ADC routine.
 * @param none
 * @return none
*/
void ADCC_Initialize(void);

/**
 * @ingroup adcc
 * @brief This API starts A/D conversion on selected channel.
 * @param channel - Analog channel number on which A/D conversion has to be applied.
 *                  Refer adcc_channel_t for available list of channels
 * @return none
*/
void ADCC_StartConversion(adcc_channel_t channel);

/**
 * @ingroup adcc
 * @brief This API checks if ongoing A/D conversion is complete.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @retval true - if conversion is complete
 * @retval false - if conversion is ongoing
*/
bool ADCC_IsConversionDone(void);

/**
 * @ingroup adcc
 * @brief This API is used to retrieve the result of latest A/D conversion.
 * @pre ADCC_StartConversion function should be called before calling this function and completion status should be checked using ADCC_IsConversionDone function.
 * @param none
 * @return The result of A/D conversion. Refer adc_result_t
*/
adc_result_t ADCC_GetConversionResult(void);

/**
 * @ingroup adcc
 * @brief This API is used to retrieve the result of single A/D conversion on given channel in single-ended mode.
 * @pre ADCC_DisableContinuousConversion function should have been called before calling this function
 * @param channel - Analog channel number on which A/D conversion has to be applied.
 *                  Refer adcc_channel_t  for available channels
 * @return The result of A/D conversion. Refer adc_result_t
*/
adc_result_t ADCC_GetSingleConversion(adcc_channel_t channel);

/**
 * @ingroup adcc
 * @brief This API is used to stop ongoing A/D conversion.
 * @pre ADCC_StartConversion function should have been called before calling this function.
 * @param none
 * @return none
*/
inline void ADCC_StopConversion(void);

/**
 * @ingroup adcc
 * @brief This API is used enable Stop On Interrupt bit.
 * @pre ADCC_EnableContinuousConversion function should have been called before calling this function.
 * @param none
 * @return none
*/
inline void ADCC_SetStopOnInterrupt(void);

/**
 * @ingroup adcc
 * @brief This API is used to discharge input sample capacitor by setting the channel to AVss.
 * @param none
 * @return none
*/
inline void ADCC_DischargeSampleCapacitor(void);

/**
 * @ingroup adcc
 * @brief This API is used to load ADC Acquisition Time Control register with specified value.
 * @param acquisitionValue - Value to be loaded in the acquisition time control register.
 * @return none
*/
void ADCC_LoadAcquisitionRegister(uint16_t acquisitionValue);

/**
 * @ingroup adcc
 * @brief This API is used to load ADC Precharge Time Control register with specified value.
 * @param prechargeTime - Value to be loaded in the precharge time control register.
 * @return none
*/
void ADCC_SetPrechargeTime(uint16_t prechargeTime);

/**
 * @ingroup adcc
 * @brief This API is used to load repeat counter with specified value.
 * @param repeatCount - Value to be loaded to repeat counter.
 * @return none
*/
void ADCC_SetRepeatCount(uint8_t repeatCount);

/**
 * @ingroup adcc
 * @brief This API retrieves the current value of ADC Repeat Count register.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @return Current value of ADC Repeat Count register
*/
uint8_t ADCC_GetCurrentCountofConversions(void);

/**
 * @ingroup adcc
 * @brief This API clears the accumulator.
 * @param none
 * @return none
*/
inline void ADCC_ClearAccumulator(void);

/**
 * @ingroup adcc
 * @brief This API retrieves 18-bit value of ADC accumulator.
 * @param none
 * @return Value of ADC accumulator.
*/
uint24_t ADCC_GetAccumulatorValue(void);

/**
 * @ingroup adcc
 * @brief This API is used to determine whether ADC accumulator has overflowed.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @retval true - ADC accumulator has overflowed
 * @retval false - ADC accumulator has not overflowed
*/
bool ADCC_HasAccumulatorOverflowed(void);

/**
 * @ingroup adcc
 * @brief This API retrieves the value of ADC Filter register.
 * @param none
 * @return 16-bit value obtained from ADFLTRH and ADFLTRL registers.
*/
uint16_t ADCC_GetFilterValue(void);

/**
 * @ingroup adcc
 * @brief This API retrieves the value of ADC Previous register.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @return 16-bit value obtained from ADPREVH and ADPREVL registers.
*/
uint16_t ADCC_GetPreviousResult(void);

/**
 * @ingroup adcc
 * @brief This API used to set value of ADC Threshold Set-point.
 * @param setPoint - 16-bit value for set point.
 * @return none
*/
void ADCC_DefineSetPoint(uint16_t setPoint);

/**
 * @ingroup adcc
 * @brief This API used to set value of ADC Upper Threshold register.
 * @param upperThreshold - 16-bit value for upper threshold.
 * @return none
*/
void ADCC_SetUpperThreshold(uint16_t upperThreshold);

/**
 * @ingroup adcc
 * @brief This API used to set value of ADC Lower Threshold register.
 * @param lowerThreshold - 16-bit value for lower threshold.
 * @return none
*/
void ADCC_SetLowerThreshold(uint16_t lowerThreshold);

/**
 * @ingroup adcc
 * @brief This API retrieves the value of ADC Set-point Error register.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @return 16-bit value obtained from ADERRH and ADERRL registers.
*/
uint16_t ADCC_GetErrorCalculation(void);

/**
 * @ingroup adcc
 * @brief This API enables double-sampling bit.
 * @param none
 * @return none
*/
inline void ADCC_EnableDoubleSampling(void);

/**
 * @ingroup adcc
 * @brief This API enables continuous conversion.
 * @param none
 * @return none
*/
inline void ADCC_EnableContinuousConversion(void);

/**
 * @ingroup adcc
 * @brief This API disables continuous conversion.
 * @param none
 * @return none
*/
inline void ADCC_DisableContinuousConversion(void);

/**
 * @ingroup adcc
 * @brief This API is used to determine if ADC error has crossed the upper threshold.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @retval true - if ERR > UTH
 * @retval false - if ERR <= UTH
*/
bool ADCC_HasErrorCrossedUpperThreshold(void);

/**
 * @ingroup adcc
 * @brief This API is used to determine if ADC error is less than the lower threshold.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @retval true - if ERR < LTH
 * @retval false - if ERR >= LTH
*/
bool ADCC_HasErrorCrossedLowerThreshold(void);

/**
 * @ingroup adcc
 * @brief This API is used retrieve the multi-stage status.
 * @pre ADCC_StartConversion function should be called before calling this function.
 * @param none
 * @return Contents of ADC STATUS register.
*/
uint8_t ADCC_GetConversionStageStatus(void);

/**
 * @ingroup adcc
 * @brief This routine is used to set the callback for the ADTI Interrupt.
 * @param Callback Function to be called
 * @return none
*/
void ADCC_SetADTIInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup adcc
 * @brief This routine is used to implement the Threshold ISR for the interrupt-driven implementations.
 * @param none
 * @return none
*/
void ADCC_ThresholdISR(void);

#endif//ADCC_H
