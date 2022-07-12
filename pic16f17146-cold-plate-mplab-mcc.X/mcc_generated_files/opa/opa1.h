/**
 * OPA1 Generated Driver API Header File
 * 
 * @file opa1.h
 * 
 * @defgroup  opa1 OPA1
 * 
 * @brief This is the generated header file for the OPA1 driver.
 *
 * @version OPA1 Driver Version 2.1.0
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

#ifndef OPA1_H
#define OPA1_H

/**
  Section: Included Files
*/
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup opa1
 * @enum OPA1_resistor_select
 * @brief Enumeration of R2/R1 resistor ratio
*/
typedef enum
{
    OPA1_R2byR1_is_0dp07,    /**<R2/R1 = 0.07*/
    OPA1_R2byR1_is_0dp14,    /**<R2/R1 = 0.14*/
    OPA1_R2byR1_is_0dp33,    /**<R2/R1 = 0.33*/
    OPA1_R2byR1_is_1,        /**<R2/R1 = 1*/
    OPA1_R2byR1_is_1dp67,    /**<R2/R1 = 1.67*/
    OPA1_R2byR1_is_3,        /**<R2/R1 = 3*/
    OPA1_R2byR1_is_7,        /**<R2/R1 = 7*/
    OPA1_R2byR1_is_15        /**<R2/R1 = 15*/
} OPA1_resistor_select;

/**
 * @ingroup opa1
 * @enum OPA1_posChannel_select
 * @brief Enumeration of available Positive Channels
*/
typedef enum
{
    OPA1_posChannel_Vss,
    OPA1_posChannel_GSEL,
    OPA1_posChannel_OPA1IN,
    OPA1_posChannel_Vdd_by_2,
    OPA1_posChannel_DAC1,
    OPA1_posChannel_DAC2
} OPA1_posChannel_select;

/**
 * @ingroup opa1
 * @enum OPA1_posSource_select
 * @brief Enumeration of available Positive Sources
*/
typedef enum
{
    OPA1_RB5_IN0_pos = 0x0,
    OPA1_RC3_IN1_pos = 0x1,
    OPA1_RA2_IN2_pos = 0x2,
    OPA1_RA0_IN3_pos = 0x3
} OPA1_posSource_select;

/**
 * @ingroup opa1
 * @enum OPA1_negChannel_select
 * @brief Enumeration of available Negative Channels
*/
typedef enum
{
    OPA1_negChannel_No_Connection = 0x0,
    OPA1_negChannel_GSEL = 0x1,
    OPA1_negChannel_OPA1IN = 0x2,
    OPA1_negChannel_DAC1 = 0x4,
    OPA1_negChannel_DAC2 = 0x5
} OPA1_negChannel_select;

/**
 * @ingroup opa1
 * @enum OPA1_negSource_select
 * @brief Enumeration of available Negative Sources
*/
typedef enum
{
    OPA1_RB4_IN0_neg = 0x0,   
    OPA1_RC3_IN1_neg = 0x1,   
    OPA1_RA2_IN2_neg = 0x2,   
    OPA1_RA0_IN3_neg = 0x3,   
    OPA1_Vss = 0x7   
} OPA1_negSource_select;

/**
 * @ingroup opa1
 * @brief This routine initializes the OPA1 and must be called before any other OPA1 routine is called.
 * This routine should only be called once during system initialization.
 * @param None
 * @return None
*/
void OPA1_Initialize(void);

/**
 * @ingroup opa1
 * @brief Enables the OPA1 Charge Pump
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param None
 * @return None
*/
inline void OPA1_EnableChargePump(void);

/**
 * @ingroup opa1
 * @brief Disables the OPA1 Charge Pump
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param None
 * @return None
*/
inline void OPA1_DisableChargePump(void);

/**
 * @ingroup opa1
 * @brief Enables OPA1 to operate with unity gain
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param None
 * @return None
*/
inline void OPA1_EnableSoftwareUnityGain(void);

/**
 * @ingroup opa1
 * @brief Disables unity gain in OPA1 
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param None
 * @return None
*/
inline void OPA1_DisableSoftwareUnityGain(void);

/**
 * @ingroup opa1
 * @brief Sets the positive channel as per user selection
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param Desired positive channel. For available positive channels refer OPA1_posChannel_select enum from opa1.h file
 * @return None
*/
inline void OPA1_SetPositiveChannel(OPA1_posChannel_select posChannel);

/**
 * @ingroup opa1
 * @brief Sets the positive source as per user selection
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param Desired positive source. For available positive sources refer OPA1_posSource_select enum from opa1.h file
 * @return None
*/
inline void OPA1_SetPositiveSource(OPA1_posSource_select posSource);

/**
 * @ingroup opa1
 * @brief Sets the negative channel as per user selection
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param Desired negative channel. For available negative channels refer OPA1_negChannel_select enum from opa1.h file
 * @return None
*/
inline void OPA1_SetNegativeChannel(OPA1_negChannel_select negChannel);

/**
 * @ingroup opa1
 * @brief Sets the negative source as per user selection
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param Desired negative source. For available negative sources refer OPA1_negSource_select enum from opa1.h file
 * @return None
*/
inline void OPA1_SetNegativeSource(OPA1_negSource_select negSource);

/**
 * @ingroup opa1
 * @brief Sets the R1 and R2 values of internal resistor ladder as per user selection
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param Desired resistor selection. For available resistor values refer OPA1_resistor_sel enum from opa1.h file
 * @return None
*/
void OPA1_SetResistorLadder(OPA1_resistor_select resistorSelection);

/**
 * @ingroup opa1
 * @brief Enables hardware override by setting the override enable bit
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param None
 * @return None
*/
inline void OPA1_EnableHardwareOverride(void);

/**
 * @ingroup opa1
 * @brief Selects the Hardware Override Source and polarity
 * @pre The OPA1_EnableHardwareOverride() routine must be called before this routine
 * @param Desired hardware override source and source polarity
 * @return None
*/
void OPA1_SetHardwareOverrideSource(uint8_t overrideSource, uint8_t polarity);

/**
 * @ingroup opa1
 * @brief Disables the hardware override by clearing the override enable bit
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param None
 * @return None
*/
inline void OPA1_DisableHardwareOverride(void);

/**
 * @ingroup opa1
 * @brief Selects the Software Override Mode
 * @pre The OPA1_DisableHardwareOverride() routine must be called before this routine
 * @param Desired software override mode
 * @return None
*/
inline void OPA1_SetSoftwareOverride(uint8_t softwareControl);

/**
 * @ingroup opa1
 * @brief Sets the input offset calibration
 * @pre opa1 should be initialized with OPA1_Initialize() before calling this API.
 * @param Desired input offset
 * @return None
*/
inline void OPA1_SetInputOffset(uint8_t offset);

#endif //OPA1_H