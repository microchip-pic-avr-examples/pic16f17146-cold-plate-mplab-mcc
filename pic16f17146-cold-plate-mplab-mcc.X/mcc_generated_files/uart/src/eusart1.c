/**
 * EUSART1 Generated Driver API Header File
 * 
 * @file eusart1.c
 * 
 * @ingroup eusart1
 * 
 * @brief This is the generated driver implementation file for the EUSART1 driver using CCL
 *
 * @version EUSART1 Driver Version 3.0.0
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

/**
  Section: Included Files
*/
#include "../eusart1.h"

/**
  Section: Macro Declarations
*/

/**
  Section: Driver Interface
 */

const uart_drv_interface_t UART1 = {
    .Initialize = &EUSART1_Initialize,
    .Deinitialize = &EUSART1_Deinitialize,
    .Read = &EUSART1_Read,
    .Write = &EUSART1_Write,
    .IsRxReady = &EUSART1_IsRxReady,
    .IsTxReady = &EUSART1_IsTxReady,
    .IsTxDone = &EUSART1_IsTxDone,
    .TransmitEnable = &EUSART1_TransmitEnable,
    .TransmitDisable = &EUSART1_TransmitDisable,
    .AutoBaudSet = NULL,
    .AutoBaudQuery = NULL,
    .BRGCountSet = NULL,
    .BRGCountGet = NULL,
    .BaudRateSet = NULL,
    .BaudRateGet = NULL,
    .AutoBaudEventEnableGet = NULL,
    .ErrorGet = &EUSART1_ErrorGet,
    .TxCompleteCallbackRegister = NULL,
    .RxCompleteCallbackRegister = NULL,
    .TxCollisionCallbackRegister = NULL,
    .FramingErrorCallbackRegister = &EUSART1_FramingErrorCallbackRegister,
    .OverrunErrorCallbackRegister = &EUSART1_OverrunErrorCallbackRegister,
    .ParityErrorCallbackRegister = NULL,
    .EventCallbackRegister = NULL,
};

/**
  Section: EUSART1 variables
*/
volatile eusart1_status_t eusart1RxLastError;

/**
  Section: EUSART1 APIs
*/

void (*EUSART1_FramingErrorHandler)(void);
void (*EUSART1_OverrunErrorHandler)(void);

static void EUSART1_DefaultFramingErrorCallback(void);
static void EUSART1_DefaultOverrunErrorCallback(void);


/**
  Section: EUSART1  APIs
*/

void EUSART1_Initialize(void)
{
    // Set the EUSART1 module to the options selected in the user interface.

    //ABDEN disabled; WUE disabled; BRG16 16bit_generator; SCKP Non-Inverted; 
    BAUD1CON = 0x48; 
    //ADDEN disabled; CREN enabled; SREN disabled; RX9 8-bit; SPEN enabled; 
    RC1STA = 0x90; 
    //TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; TXEN enabled; TX9 8-bit; CSRC client; 
    TX1STA = 0x26; 
    //SPBRGL 64; 
    SP1BRGL = 0x40; 
    //SPBRGH 3; 
    SP1BRGH = 0x3; 

    EUSART1_FramingErrorCallbackRegister(EUSART1_DefaultFramingErrorCallback);
    EUSART1_OverrunErrorCallbackRegister(EUSART1_DefaultOverrunErrorCallback);
    eusart1RxLastError.status = 0;  

}

void EUSART1_Deinitialize(void)
{
    BAUD1CON = 0x00;
    RC1STA = 0x00;
    TX1STA = 0x00;
    SP1BRGL = 0x00;
    SP1BRGH = 0x00;
}

inline void EUSART1_Enable(void)
{
    RC1STAbits.SPEN = 1;

}

inline void EUSART1_Disable(void)
{
    RC1STAbits.SPEN = 0;
}

inline void EUSART1_TransmitEnable(void)
{
    TX1STAbits.TXEN = 1;
}

inline void EUSART1_TransmitDisable(void)
{
    TX1STAbits.TXEN = 0;
}

inline void EUSART1_ReceiveEnable(void)
{
    RC1STAbits.CREN = 1;
}

inline void EUSART1_ReceiveDisable(void)
{
    RC1STAbits.CREN = 0;
}

inline void EUSART1_SendBreakControlEnable(void)
{
    TX1STAbits.SENDB = 1;
}

inline void EUSART1_SendBreakControlDisable(void)
{
    TX1STAbits.SENDB = 0;
}

bool EUSART1_IsRxReady(void)
{
    return (bool)(PIR4bits.RC1IF);
}

bool EUSART1_IsTxReady(void)
{
    return (bool)(PIR4bits.TX1IF && TX1STAbits.TXEN);
}

bool EUSART1_IsTxDone(void)
{
    return TX1STAbits.TRMT;
}

size_t EUSART1_ErrorGet(void)
{
    return eusart1RxLastError.status;
}

uint8_t EUSART1_Read(void)
{
    eusart1RxLastError.status = 0;
    if(RC1STAbits.OERR)
    {
        eusart1RxLastError.oerr = 1;
        if(NULL != EUSART1_OverrunErrorHandler)
        {
            EUSART1_OverrunErrorHandler();
        }   
    }
    if(RC1STAbits.FERR)
    {
        eusart1RxLastError.ferr = 1;
        if(NULL != EUSART1_FramingErrorHandler)
        {
            EUSART1_FramingErrorHandler();
        }   
    }
    return RC1REG;
}

void EUSART1_Write(uint8_t txData)
{
    TX1REG = txData;
}

static void EUSART1_DefaultFramingErrorCallback(void)
{
    
}

static void EUSART1_DefaultOverrunErrorCallback(void)
{
    //Continuous Receive must be cleared to clear Overrun Error else Rx will not receive upcoming bytes
    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
}

void EUSART1_FramingErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        EUSART1_FramingErrorHandler = callbackHandler;
    }
}

void EUSART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        EUSART1_OverrunErrorHandler = callbackHandler;
    }    
}

