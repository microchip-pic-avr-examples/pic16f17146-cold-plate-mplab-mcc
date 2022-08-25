/**
 * CRC Generated Driver File
 * 
 * @file crc.h
 * 
 * @ingroup  crc
 * 
 * @brief This is the generated driver implementation file for the CRC driver.
 *
 * @version CRC Driver Version 1.0.0
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

#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stdbool.h>

/**
  Section: CRC Module APIs
*/

/**
 * @ingroup crc
 * @brief This API initializes the CRC module. This routine must be called before any other CRC routine.
 * @param none
 * @return none
 */
void CRC_Initialize(void);

/**
 * @ingroup crc
 * @brief This API sets the CRCGO bit to begin the shifting process.
 * @param none
 * @return none
 */
inline void CRC_StartCrc(void);

/**
 * @ingroup crc
 * @brief This API writes data into CRCDATA registers.
 * @param data: CRC input data
 * @retVal true - if CRCDATA registers are written
 * @retVal false - if CRCDATA registers are not written
 */
bool CRC_WriteData(uint32_t data);

/**
 * @ingroup crc
 * @brief This API reads and returns the normal or reverse crc result value.
 * @param reverse: false - Normal value, true - Reverse value
 *        xorValue: value which xored with CRC result.
 * @return {moduleNameUpperCase} result
 */
uint32_t CRC_GetCalculatedResult(bool reverse, uint32_t xorValue);

/**
 * @ingroup crc
 * @brief This API returns the CRCBUSY bit value to check CRC calculation is over or not.
 * @param none
 * @retVal true - CRC is busy.
 * @retVal false - CRC is not busy.
 */
inline bool CRC_IsCrcBusy(void);

/**
 * @ingroup crc
 * @brief This API starts scanning process.
 * @param none
 * @return none
 */
inline void CRC_StartScanner(void);

/**
 * @ingroup crc
 * @brief This API stops scanning process.
 * @param none
 * @return none
 */
inline void CRC_StopScanner(void);

/**
 * @ingroup crc
 * @brief This API sets the memory address limit for scanner
 * @param startAddr: Starting address of memory block.
 *          endAddr: Ending address of memory block.
 * @return none
 */
void CRC_SetScannerAddressLimit(uint16_t startAddr, uint16_t endAddr);

/**
 * @ingroup crc
 * @brief This API returns the status of SCANBUSY bit.
 * @param none
 * @retVal true - Scanner cycle is in process.
 * @retVal false - Scanner cycle is complete (or not yet started).
 */
inline bool CRC_IsScannerBusy(void);


#endif //CRC_H