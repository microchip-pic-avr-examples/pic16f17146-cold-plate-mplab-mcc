/**
 *
 * @file nvm.c
 *
 * @ingroup nvm_driver
 *
 * @brief This file contains the implementation for NVM driver
 *
 * @version NVM Driver Version 3.0.0
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

#include <stdbool.h>
#include "../nvm.h"

volatile static uint8_t unlockKeyLow;
volatile static uint8_t unlockKeyHigh;

void NVM_Initialize(void)
{
    //No initialization needed
}

bool NVM_IsBusy(void)
{
    return (NVMCON1bits.WR || NVMCON1bits.RD);
}

nvm_status_t NVM_StatusGet(void)
{
    if (NVMCON1bits.WRERR == 1)
    {
        return NVM_ERROR;
    }
    else
    {
        return NVM_OK;
    }
}

void NVM_StatusClear(void)
{
    NVMCON1bits.WRERR = 0;
}

void NVM_UnlockKeySet(uint16_t unlockKey)
{
    unlockKeyHigh = (uint8_t) (unlockKey >> 8);
    unlockKeyLow = (uint8_t) unlockKey;
}

void NVM_UnlockKeyClear(void)
{
    unlockKeyHigh = 0x00;
    unlockKeyLow = 0x00;
}

flash_data_t FLASH_Read(flash_address_t address)
{
    //Load NVMADR with address of the word
    NVMADRH = (uint8_t) (address >> 8);
    NVMADRL = (uint8_t) address;

    //Access Program Flash Memory
    NVMCON1bits.NVMREGS = 0;    
    
    //Initiate Read
    NVMCON1bits.RD = 1;      

    return ((flash_data_t) ((NVMDATH << 8) | NVMDATL));
}

nvm_status_t FLASH_RowWrite(flash_address_t address, flash_data_t *dataBuffer)
{
    uint8_t unlockKeyLowLocal = unlockKeyLow;
    uint8_t unlockKeyHighLocal = unlockKeyHigh;

    uint8_t flashDataCount = PROGMEM_PAGE_SIZE;
    
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;   

    //Access program Flash memory
    NVMCON1bits.NVMREGS = 0;   
    
    //Enable write operation
    NVMCON1bits.WREN = 1;   
    
    //Load Write Latches Only
    NVMCON1bits.LWLO = 1;   
    
    while (flashDataCount-- > 0U)
    {
        NVMADRH = (uint8_t) (address >> 8);
        NVMADRL = (uint8_t) address;
        address++;
        
        NVMDATH = (uint8_t) (*dataBuffer >> 8);
        NVMDATL = (uint8_t) (*dataBuffer);
        dataBuffer++;
        
        //If last latch to be written
        if (flashDataCount == 0U)
        {
            //Write program Flash memory 
            NVMCON1bits.LWLO = 0;
        }
        
        //Disable global interrupt
        INTCONbits.GIE = 0;    
        
        //Perform the unlock sequence
        NVMCON2 = unlockKeyLowLocal;
        NVMCON2 = unlockKeyHighLocal;
        NVMCON1bits.WR = 1;
          
        //Restore global interrupt enable bit value
        INTCONbits.GIE = globalInterruptBitValue; 
    }
    
    //Disable write operation
    NVMCON1bits.WREN = 0;      
    
    if (NVMCON1bits.WRERR == 1) 
    {
        return NVM_ERROR;
    } 
    else 
    {
        return NVM_OK;
    }
}

nvm_status_t FLASH_PageErase(flash_address_t address)
{
    uint8_t unlockKeyLowLocal = unlockKeyLow;
    uint8_t unlockKeyHighLocal = unlockKeyHigh;

    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;    
    
    //Load NVMADR with the start address of the memory row
    NVMADRH = (uint8_t) (address >> 8);
    NVMADRL = (uint8_t) address;

    //Access program Flash memory
    NVMCON1bits.NVMREGS = 0;
    
    //Performs an erase operation with the next WR command
    NVMCON1bits.FREE = 1;   
    
    //Enable erase operation
    NVMCON1bits.WREN = 1;    

    //Disable global interrupt
    INTCONbits.GIE = 0; 
    
    //Perform the unlock sequence
    NVMCON2 = unlockKeyLowLocal;
    NVMCON2 = unlockKeyHighLocal;
    NVMCON1bits.WR = 1;
    
    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue;	

    //Disable erase operation
    NVMCON1bits.WREN = 0;      
    
    if (NVMCON1bits.WRERR == 1) 
    {
        return NVM_ERROR;
    } 
    else 
    {
        return NVM_OK;
    }
}

flash_address_t FLASH_ErasePageAddressGet(flash_address_t address)
{
    return (flash_address_t) (address & ((PROGMEM_SIZE - 1U) ^ (PROGMEM_PAGE_SIZE - 1U)));
}

uint16_t FLASH_ErasePageOffsetGet(flash_address_t address)
{
    return (uint16_t) (address & (PROGMEM_PAGE_SIZE - 1U));
}

eeprom_data_t EEPROM_Read(eeprom_address_t address)
{
    //Access EEPROM
    NVMCON1bits.NVMREGS = 1;  
    
    //Load NVMADR with the EEPROM address
    NVMADRH = (uint8_t) (address >> 8);
    NVMADRL = (uint8_t) address;
    
    //Initiate Read
    NVMCON1bits.RD = 1;

    return NVMDATL;
}

void EEPROM_Write(eeprom_address_t address, eeprom_data_t data)
{
    uint8_t unlockKeyLowLocal = unlockKeyLow;
    uint8_t unlockKeyHighLocal = unlockKeyHigh;

    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;

    //Access EEPROM
    NVMCON1bits.NVMREGS = 1;
    
    //Enable write operation
    NVMCON1bits.WREN = 1;

    //Load NVMADR with the EEPROM address
    NVMADRH = (uint8_t) (address >> 8);
    NVMADRL = (uint8_t) address;

    //Load NVMDAT with the desired value
    NVMDATL = data;

    //Disable global interrupt
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    NVMCON2 = unlockKeyLowLocal;
    NVMCON2 = unlockKeyHighLocal;
    NVMCON1bits.WR = 1;

    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue; 

    //Disable write operation
    NVMCON1bits.WREN = 0;
}
