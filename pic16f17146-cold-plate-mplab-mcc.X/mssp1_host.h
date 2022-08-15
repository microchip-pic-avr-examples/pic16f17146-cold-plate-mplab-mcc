/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

#ifndef MSSP1_HOST_H
#define	MSSP1_HOST_H

#include <stdint.h>
#include <stdbool.h>

//If set, the I2C pins are set to use the pull-up resistors
//#define USE_INTERNAL_PULLUPS

    /**
     * <b><FONT COLOR=BLUE>void</FONT> initI2CPins(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     * Initializes the pins used by the MSSP for I2C communication.
     */
    void initI2CPins(void);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> MSSP_HostInit(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     * Initializes the registers of the MSSP for host mode.
     * Driver operates in polled mode at 100 kHz.
     */
    void MSSP_HostInit(void); 
    
    /**
     * <b><FONT COLOR=BLUE>bool</FONT> MSSP_RegisterSelectAndRead(<FONT COLOR=BLUE>uint8_t</FONT> deviceADDR, <FONT COLOR=BLUE>uint8_t</FONT> registerADDR, <FONT COLOR=BLUE>uint8_t</FONT>* blockMem, <FONT COLOR=BLUE>uint8_t</FONT> memSize)</B>
     * @param deviceADDR (uint8_t) - 7-bit I2C Address of Client
     * @param registerADDR (uint8_t) - 8-bit address of register to select
     * @param blockMem (uint8_t*) - Location of block memory to store data
     * @param memSize (uint8_t) - Amount of memory to read
     * 
     * This function selects the client device, writes the register address, restarts the bus, then reads memSize bytes from the device.
     * Returns true if transfer was successful, or false if a NACK was received.
     */
    bool MSSP_RegisterSelectAndRead(uint8_t deviceADDR, uint8_t registerADDR, uint8_t* blockMem, uint8_t memSize); 

    /**
     * <b><FONT COLOR=BLUE>bool</FONT> MSSP_WriteByte(<FONT COLOR=BLUE>uint8_t</FONT> deviceADDR, <FONT COLOR=BLUE>uint8_t</FONT> data)</B>
     * @param deviceADDR (uint8_t) - 7-bit I2C Address of Client
     * @param data (uint8_t) - Byte of data to send
     * 
     * This function selects the client device and writes a single byte of data to it.
     * Returns true if transfer was successful, or false if a NACK was received.
     */
    bool MSSP_WriteByte(uint8_t deviceADDR, uint8_t data);
    
    /**
     * <b><FONT COLOR=BLUE>bool</FONT> MSSP_ReadByte(<FONT COLOR=BLUE>uint8_t</FONT> deviceADDR, <FONT COLOR=BLUE>uint8_t</FONT>* data)</B>
     * @param deviceADDR (uint8_t) - 7-bit I2C Address of Client
     * @param data (uint8_t*) - Byte of data to store
     * 
     * This function selects the client device and reads a single byte of data from it.
     * Returns true if transfer was successful, or false if a NACK was received.
     */
    bool MSSP_ReadByte(uint8_t deviceADDR, uint8_t* data);
    
    /**
     * <b><FONT COLOR=BLUE>uint8_t</FONT> MSSP_ReadByteNoWarn(<FONT COLOR=BLUE>uint8_t</FONT> deviceADDR)</B>
     * @param deviceADDR (uint8_t) - 7-bit I2C Address of Client
     * 
     * This function selects the client device and reads a single byte of data from it.
     * Returns 0x00 (on a failure) or the byte of data received. 
     */
    uint8_t MSSP_ReadByteNoWarn(uint8_t deviceADDR);

    /**
     * <b><FONT COLOR=BLUE>bool</FONT> MSSP_WriteBlock(<FONT COLOR=BLUE>uint8_t</FONT> deviceADDR, <FONT COLOR=BLUE>uint8_t*</FONT> blockMem, <FONT COLOR=BLUE>uint8_t</FONT> memSize)</B>
     * @param deviceADDR (uint8_t) - 7-bit I2C Address of Client
     * @param blockMem (uint8_t*) - Block of memory to write
     * @param memSize (uint8_t) - Amount of memory to write
     * 
     * This function selects the client device and writes a block of memory to it.
     * Returns true if transfer was successful, or false if a NACK was received.
     */
    bool MSSP_WriteBlock(uint8_t deviceADDR, uint8_t* blockMem, uint8_t memSize);
    
    /**
     * <b><FONT COLOR=BLUE>bool</FONT> MSSP_ReadBlock(<FONT COLOR=BLUE>uint8_t</FONT> deviceADDR, <FONT COLOR=BLUE>uint8_t*</FONT> blockMem, <FONT COLOR=BLUE>uint8_t</FONT> memSize)</B>
     * @param deviceADDR (uint8_t) - 7-bit I2C Address of Client
     * @param blockMem (uint8_t*) - Block of memory to store to
     * @param memSize (uint8_t) - Amount of memory to read
     * 
     * This function selects the client device and reads a block of memory from it.
     * Returns true if transfer was successful, or false if a NACK was received.
     */
    bool MSSP_ReadBlock(uint8_t deviceADDR, uint8_t* blockMem, uint8_t memSize);


#endif

