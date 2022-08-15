/*
Copyright (c) 2013 - 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "mssp1_host.h"

// MSSP defines and macros
#define MSSP_IDLE       !(SSP1STATbits.R_nW | (0x1F & SSP1CON2))                // I2C Idle
#define MSSP_START      (SSP1CON2bits.SEN)                                      // I2C Start 
#define MSSP_RESTART    (SSP1CON2bits.RSEN)                                     // I2C Restart
#define MSSP_STOP       (SSP1CON2bits.PEN)                                      // I2C Stop
#define MSSP_NACKED     (SSP1CON2bits.ACKSTAT)                                  // Returns true if the client NACK'ed, false if the client ACK'ed

#define WriteByteToMSSP(X) do { SSP1BUF = X; while (!MSSP_IDLE); } while (0)

inline void stopI2C(void)
{
    //Set the Stop bit 
    MSSP_STOP = 1; 
    
    //Wait until MSSP module is idle
    while (!MSSP_IDLE);
    NOP();
}

inline bool startI2CWrite(uint8_t addr)
{
    //Wait until MSSP module is idle
    while (!MSSP_IDLE);                                           

    //Set the Start bit
    MSSP_START = 1; 
    
    //Wait until hardware clears the SEN bit
    while (MSSP_START); 

    //Send the I2C Address
    WriteByteToMSSP(addr << 1); 
    
    //If NACKed, stop I2C communication
    if (MSSP_NACKED)
    {
        stopI2C();
        return false;
    }
    
    return true;
}

inline bool startI2CRead(uint8_t addr)
{
    //Wait until MSSP module is idle
    while (!MSSP_IDLE);                                                         

    //Set the Start Bit
    MSSP_START = 1;            
    
    //Wait until hardware clears the SEN bit 
    while (MSSP_START);                                                         

    //Load device address (read)
    WriteByteToMSSP((addr << 1) | 0b1);                                         
    
    //If NACKed, stop I2C communication
    if (MSSP_NACKED)
    {
        stopI2C();
        return false;
    }
    
    return true;
}

void initI2CPins(void)
{
    //RB4 = SDA, RB6 = SCL
    
    //RC7 = SDA, RB7 = SCL
    TRISCbits.TRISC7 = 0b1;
    TRISBbits.TRISB7 = 0b1;
    
    //Disable analog mode
    ANSELCbits.ANSC7 = 0b0;
    ANSELBbits.ANSB7 = 0b0;
    
    //Enable Open-Drain Outputs
    ODCONCbits.ODCC7 = 0b1;
    ODCONBbits.ODCB7 = 0b1;
    
#ifdef USE_INTERNAL_PULLUPS
    
    //Settings for I2C Pins
    //Standard Slew Rate, 2x standard pull-up current, I2C Thresholds
    
    RB4I2C = 0b00010001;
    RB6I2C = 0b00010001;
    
#endif
    
    //PPS Settings
    RC7PPS = 0x1C;
    RB7PPS = 0x1B;
    
    SSP1DATPPS = 0b010111;
    SSP1CLKPPS = 0b001111;
}

void MSSP_HostInit(void) 
{   
    //Reset Registers
    SSP1CON1 = 0x00;
    SSP1STAT = 0x00;
    SSP1CON2 = 0x00;
    SSP1CON3 = 0x00;
    
    //I2C in Standard Speed Mode
    SSP1STATbits.SMP = 0b1;
    
    //I2C Host Mode, Clk = Fosc/4(SSPxADD + 1)
    SSP1CON1bits.SSPM = 0b1000;
    
    //0x4F = 100 kHz Clock @ 32 MHz
    SSP1ADD = 0x4F;                                                             
    
    // Clear the host interrupt flag
    PIR5bits.SSP1IF = 0;
    
    // Disable the host interrupt
    PIE5bits.SSP1IE = 0;
    
    // Enable the MSSP Peripheral
    SSP1CON1bits.SSPEN = 0b1; 
}

bool MSSP_RegisterSelectAndRead(uint8_t deviceADDR, uint8_t registerADDR, uint8_t* blockMem, uint8_t memSize)                    
{
    //Start I2C - if NACKed, exit
    if (!startI2CWrite(deviceADDR))                                             
    {
        return false;
    }
    
    //Send register address
    WriteByteToMSSP(registerADDR);

    //Begin Restart Sequence
    MSSP_RESTART = 1;                                                           
    while (MSSP_RESTART);

    //Load device address (read)
    WriteByteToMSSP((deviceADDR << 1) | 0b1);

    //If NACKed, stop I2C communication
    if (MSSP_NACKED)
    {
        stopI2C();
        return false;
    }
    
    // Read x number of bytes
    for (uint8_t I2CReads = 0; I2CReads < memSize; I2CReads++)
    {
        //Set Receive Enable bit (Host as a receiver)
        SSP1CON2bits.RCEN = 1; 
        
        //Wait until MSSP module is idle
        while (!MSSP_IDLE);

        //Put each byte into array
        blockMem[I2CReads] = SSP1BUF;

        if (I2CReads == memSize - 1) 
        {
            //ACKDT = Acknowledge Bit. 1 = NACK, 0 = ACK
            
            //NACK the Client
            SSP1CON2bits.ACKDT = 1;
            
            //Begin NACK Sequence
            SSP1CON2bits.ACKEN = 1; 
            while (SSP1CON2bits.ACKEN);
        } 
        else 
        {
            //ACKDT = Acknowledge Bit. 1 = NACK, 0 = ACK
            
            //ACK the Client
            SSP1CON2bits.ACKDT = 0;
            
            //Begin ACK Sequence
            SSP1CON2bits.ACKEN = 1;
            
            //Wait until MSSP module is idle
            while (!MSSP_IDLE);
        }
    }
    
    //Stop I2C Communication
    stopI2C();
    return true;
}

bool MSSP_WriteByte(uint8_t deviceADDR, uint8_t data)
{
    //Start I2C - if NACKed, exit
    if (!startI2CWrite(deviceADDR))
    {
        return false;
    }
    
    //Send a Byte of Data
    WriteByteToMSSP(data); 
    
    //Stop I2C Communication
    stopI2C();
    return true;

}

bool MSSP_ReadByte(uint8_t deviceADDR, uint8_t* data)
{
    //Start I2C - if NACKed, exit
    if (!startI2CRead(deviceADDR))                                            
    {
        return false;
    }
    
    //Set Receive Enable bit (Host as a receiver)
    SSP1CON2bits.RCEN = 1;
    
    //Wait until MSSP module is idle
    while (!MSSP_IDLE);

    //Store the byte
    *data = SSP1BUF;

    //Acknowledge bit, 1 = Not acknowledge
    SSP1CON2bits.ACKDT = 1;
    
    //Start NACK Sequence 
    SSP1CON2bits.ACKEN = 1;
    
    //Wait for end of acknowledge sequence
    while (SSP1CON2bits.ACKEN);
    
    //Stop I2C Communication
    stopI2C();
    return true;
}

uint8_t MSSP_ReadByteNoWarn(uint8_t deviceADDR)
{
    uint8_t readByte = 0x00;
    
    //Call the read byte function
    MSSP_ReadByte(deviceADDR, &readByte);
    
    //Return the result
    return readByte;
}

bool MSSP_WriteBlock(uint8_t deviceADDR, uint8_t* blockMem, uint8_t memSize)
{
    //Start I2C - if NACKed, exit
    if (!startI2CWrite(deviceADDR))
    {
        return false;
    }
    
    bool success = true;
    //Send the block of memory to the client
    for (uint8_t I2CWrites = 0; I2CWrites < memSize; I2CWrites++)
    {
        //Send a byte of data
        WriteByteToMSSP(blockMem[I2CWrites]);
        
        if (MSSP_NACKED)
        {
            I2CWrites = memSize;
            success = false;
        }
    }
    
    //Stop I2C Communication
    stopI2C();
    return success;
}

bool MSSP_ReadBlock(uint8_t deviceADDR, uint8_t* blockMem, uint8_t memSize)
{
    // Start I2C - if NACKed, exit
    if (!startI2CRead(deviceADDR))
    {
        return false;
    }
    
    //Read x number of bytes
    for (uint8_t I2CReads = 0; I2CReads < memSize; I2CReads++)                  
    {
        //Set Receive Enable bit (Host as a receiver)
        SSP1CON2bits.RCEN = 1; 
        
        //Wait until MSSP module is idle
        while (!MSSP_IDLE); 

        //Store each byte
        blockMem[I2CReads] = SSP1BUF;

        if (I2CReads == memSize - 1) 
        {
            //ACKDT = Acknowledge Bit. 1 = NACK, 0 = ACK
            
            //NACK the Client
            SSP1CON2bits.ACKDT = 1;
            
            //Begin NACK Sequence
            SSP1CON2bits.ACKEN = 1; 
            while (SSP1CON2bits.ACKEN);
        } 
        else 
        {
            //ACKDT = Acknowledge Bit. 1 = NACK, 0 = ACK
            
            //ACK the Client
            SSP1CON2bits.ACKDT = 0;
            
            //Begin ACK Sequence
            SSP1CON2bits.ACKEN = 1;
            
            //Wait until MSSP module is idle
            while (!MSSP_IDLE);
        }
    }
    
    //Stop I2C Communication
    stopI2C();
    return true;
}