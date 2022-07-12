/**
 * MSSP1 Generated Driver File
 *
 * @file mssp1.c
 *
 * @ingroup i2c_host
 *
 * @brief This file contains the driver code for I2C1 module.
 *
 * @version I2C1 Driver Version 2.1.0
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

#include <xc.h>
#include "../mssp1.h"

/* I2C1 event system interfaces */
static void I2C1_ReadStart(void);
static void I2C1_WriteStart(void);
static void I2C1_Close(void);
static void I2C1_EventHandler(void);
static void I2C1_ErrorEventHandler(void);
static void I2C1_DefaultCallback(void);

/* I2C1 Interfaces */
static uint8_t I2C1_DataReceive(void);
static void I2C1_DataTransmit(uint8_t data);
static inline void I2C1_BusReset(void);
static inline void I2C1_ReceiveEnable(void);
static inline void I2C1_RestartEnable(void);
static inline void I2C1_RestartDisable(void);
static inline void I2C1_StartSend(void);
static inline void I2C1_StopSend(void);
static inline void I2C1_AckSend(void);
static inline void I2C1_NackSend(void);
static bool I2C1_IsNack(void);
static bool I2C1_IsData(void);
static bool I2C1_IsAddr(void);
static bool I2C1_IsRxBufFull(void);
static inline void I2C1_InterruptClear(void);
static inline void I2C1_ErrorInterruptClear(void);
static inline void I2C1_StatusFlagsClear(void);

static i2c_host_event_states_t I2C1_EVENT_IDLE(void);
static i2c_host_event_states_t I2C1_EVENT_SEND_RD_ADDR(void);
static i2c_host_event_states_t I2C1_EVENT_SEND_WR_ADDR(void);
static i2c_host_event_states_t I2C1_EVENT_TX(void);
static i2c_host_event_states_t I2C1_EVENT_RX(void);
static i2c_host_event_states_t I2C1_EVENT_NACK(void);
static i2c_host_event_states_t I2C1_EVENT_ERROR(void);
static i2c_host_event_states_t I2C1_EVENT_STOP(void);
static i2c_host_event_states_t I2C1_EVENT_RESET(void);

/*
  Section: Driver Interface
 */
const i2c_host_interface_t I2C1_Host = {
    .Initialize = I2C1_Initialize,
    .Deinitialize = I2C1_Deinitialize,
    .Write = I2C1_Write,
    .Read = I2C1_Read,
    .WriteRead = I2C1_WriteRead,
    .TransferSetup = NULL,
    .ErrorGet = I2C1_ErrorGet,
    .IsBusy = I2C1_IsBusy,
    .CallbackRegister = I2C1_CallbackRegister,
    .Tasks = I2C1_Tasks
};

/*
 Section: Private Variable Definitions
 */
static void (*I2C1_Callback)(void) = NULL;
volatile i2c_host_event_status_t i2c1Status = {0};

typedef i2c_host_event_states_t (*i2c1eventHandler)(void);
const i2c1eventHandler i2c1_eventTable[] = {
    I2C1_EVENT_IDLE,
    I2C1_EVENT_SEND_RD_ADDR,
    I2C1_EVENT_SEND_WR_ADDR,
    I2C1_EVENT_TX,
    I2C1_EVENT_RX,
    I2C1_EVENT_NACK,
    I2C1_EVENT_ERROR,
    I2C1_EVENT_STOP,
    I2C1_EVENT_RESET
};

/**
 Section: Public Interfaces
 */
void I2C1_Initialize(void)
{
    /* CKE disabled; SMP Standard Speed;  */
    SSP1STAT = 0x80;
    /* SSPM FOSC/4_SSPxADD_I2C; CKP disabled; SSPEN disabled;  */
    SSP1CON1 = 0x8;
    /* SEN disabled; RSEN disabled; PEN disabled; RCEN disabled; ACKEN disabled; ACKDT acknowledge; GCEN disabled;  */
    SSP1CON2 = 0x0;
    /* DHEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; BOEN disabled; SCIE disabled; PCIE disabled;  */
    SSP1CON3 = 0x0;
    /* SSPADD 79;  */
    SSP1ADD = 0x4F;
    I2C1_CallbackRegister(I2C1_DefaultCallback);
    SSP1CON1bits.SSPEN = 1;
}

void I2C1_Deinitialize(void)
{
    SSP1STAT = 0x00;
    SSP1CON1 = 0x00;
    SSP1CON2 = 0x00;
    SSP1CON3 = 0x00;
    SSP1ADD = 0x00;
    I2C1_CallbackRegister(I2C1_DefaultCallback);
}

bool I2C1_Write(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!I2C1_IsBusy())
    {
        i2c1Status.busy = true;
        i2c1Status.address = address;
        i2c1Status.switchToRead = false;
        i2c1Status.writePtr = data;
        i2c1Status.writeLength = dataLength;
        i2c1Status.readPtr = NULL;
        i2c1Status.readLength = 0;
        i2c1Status.errorState = I2C_ERROR_NONE;
        I2C1_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

bool I2C1_Read(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!I2C1_IsBusy())
    {
        i2c1Status.busy = true;
        i2c1Status.address = address;
        i2c1Status.switchToRead = false;
        i2c1Status.readPtr = data;
        i2c1Status.readLength = dataLength;
        i2c1Status.writePtr = NULL;
        i2c1Status.writeLength = 0;
        i2c1Status.errorState = I2C_ERROR_NONE;
        I2C1_ReadStart();
        retStatus = true;
    }
    return retStatus;
}

bool I2C1_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength)
{
    bool retStatus = false;
    if (!I2C1_IsBusy())
    {
        i2c1Status.busy = true;
        i2c1Status.address = address;
        i2c1Status.switchToRead = true;
        i2c1Status.writePtr = writeData;
        i2c1Status.writeLength = writeLength;
        i2c1Status.readPtr = readData;
        i2c1Status.readLength = readLength;
        i2c1Status.errorState = I2C_ERROR_NONE;
        I2C1_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

i2c_host_error_t I2C1_ErrorGet(void)
{
    i2c_host_error_t retErrorState = i2c1Status.errorState;
    i2c1Status.errorState = I2C_ERROR_NONE;
    return retErrorState;
}

bool I2C1_IsBusy(void)
{
    return i2c1Status.busy || SSP1STATbits.S;
}

void I2C1_CallbackRegister(void (*callbackHandler)(void))
{
    if (callbackHandler != NULL)
    {
        I2C1_Callback = callbackHandler;
    }
}

void I2C1_Tasks(void)
{
    if (PIR5bits.BCL1IF)
    {
        I2C1_ErrorEventHandler();
    }
    if (PIR5bits.SSP1IF)
    {
        if (PIR5bits.BCL1IF)
        {
            I2C1_ErrorEventHandler();
        }
        else
        {
            I2C1_EventHandler();
        }
    }
}

/*
 Section: Private Interfaces
 */
static void I2C1_ReadStart(void)
{
    I2C1_StartSend();
    i2c1Status.state = I2C_STATE_SEND_RD_ADDR;
}

static void I2C1_WriteStart(void)
{
    I2C1_StartSend();
    i2c1Status.state = I2C_STATE_SEND_WR_ADDR;
}

static void I2C1_Close(void)
{
    i2c1Status.busy = false;
    i2c1Status.address = 0xFF;
    i2c1Status.writePtr = NULL;
    i2c1Status.readPtr = NULL;
    i2c1Status.state = I2C_STATE_IDLE;
    I2C1_InterruptClear();
    I2C1_ErrorInterruptClear();
    I2C1_StatusFlagsClear();
}

static void I2C1_EventHandler(void)
{
    I2C1_InterruptClear();
    if (I2C1_IsAddr() && I2C1_IsNack())
    {
        i2c1Status.state = I2C_STATE_NACK;
        i2c1Status.errorState = I2C_ERROR_ADDR_NACK;
    }
    else if (I2C1_IsData() && I2C1_IsNack())
    {
        i2c1Status.state = I2C_STATE_NACK;
        i2c1Status.errorState = I2C_ERROR_DATA_NACK;
    }
    i2c1Status.state = i2c1_eventTable[i2c1Status.state]();
}

static void I2C1_ErrorEventHandler(void)
{
    i2c1Status.state = I2C_STATE_ERROR;
    i2c1Status.errorState = I2C_ERROR_BUS_COLLISION;
    I2C1_ErrorInterruptClear();
    i2c1Status.state = i2c1_eventTable[i2c1Status.state]();
    I2C1_Callback();
}

static void I2C1_DefaultCallback(void)
{
    // Default Callback for Error Indication
}

/* I2C1 Event interfaces */
static i2c_host_event_states_t I2C1_EVENT_IDLE(void)
{
    i2c1Status.busy = false;
    return I2C_STATE_RESET;
}

static i2c_host_event_states_t I2C1_EVENT_SEND_RD_ADDR(void)
{
    I2C1_DataTransmit((uint8_t) (i2c1Status.address << 1 | 1));
    return I2C_STATE_RX;
}

static i2c_host_event_states_t I2C1_EVENT_SEND_WR_ADDR(void)
{
    I2C1_DataTransmit((uint8_t) (i2c1Status.address << 1));
    return I2C_STATE_TX;
}

static i2c_host_event_states_t I2C1_EVENT_TX(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_TX;
    if (i2c1Status.writeLength)
    {
        i2c1Status.writeLength--;
        I2C1_DataTransmit(*i2c1Status.writePtr++);
        retEventState = I2C_STATE_TX;
    }
    else
    {
        if (i2c1Status.switchToRead)
        {
            i2c1Status.switchToRead = false;
            I2C1_RestartEnable();
            retEventState = I2C_STATE_SEND_RD_ADDR;
        }
        else
        {
            retEventState = I2C1_EVENT_STOP();
        }
    }

    return retEventState;
}

static i2c_host_event_states_t I2C1_EVENT_RX(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_RX;

    if (I2C1_IsRxBufFull())
    {
        if (i2c1Status.readLength > 0)
        {
            *i2c1Status.readPtr++ = I2C1_DataReceive();
            i2c1Status.readLength--;

        }

        if (i2c1Status.readLength > 0)
        {
            I2C1_AckSend();
        }
        else
        {
            I2C1_RestartDisable();
            I2C1_NackSend();
            retEventState = I2C_STATE_STOP;
        }

    }
    else
    {
        I2C1_ReceiveEnable();
    }
    return retEventState;
}

static i2c_host_event_states_t I2C1_EVENT_NACK(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_NACK;
    retEventState = I2C1_EVENT_STOP();
    return retEventState;
}

static i2c_host_event_states_t I2C1_EVENT_ERROR(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_ERROR;
    retEventState = I2C1_EVENT_RESET();
    return retEventState;
}

static i2c_host_event_states_t I2C1_EVENT_STOP(void)
{
    I2C1_StopSend();
    I2C1_Close();
    return I2C_STATE_IDLE;
}

static i2c_host_event_states_t I2C1_EVENT_RESET(void)
{
    I2C1_BusReset();
    i2c1Status.busy = false;
    return I2C_STATE_IDLE;
}

/*
 Section: Register Level Interfaces
 */
static uint8_t I2C1_DataReceive(void)
{
    return SSP1BUF;
}

static void I2C1_DataTransmit(uint8_t data)
{
    SSP1BUF = data;
}

static inline void I2C1_BusReset(void)
{
    SSP1CON1bits.SSPEN = 0;
    SSP1CON1bits.SSPEN = 1;
}

static inline void I2C1_ReceiveEnable(void)
{
    SSP1CON2bits.RCEN = 1;
}

static inline void I2C1_RestartEnable(void)
{
    SSP1CON2bits.RSEN = 1;
}

static inline void I2C1_RestartDisable(void)
{
    SSP1CON2bits.RSEN = 0;
}

static inline void I2C1_StartSend(void)
{
    SSP1CON2bits.SEN = 1;
}

static inline void I2C1_StopSend(void)
{
    SSP1CON2bits.PEN = 1;
}

static inline void I2C1_AckSend(void)
{
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
}

static inline void I2C1_NackSend(void)
{
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
}

static bool I2C1_IsNack(void)
{
    return SSP1CON2bits.ACKSTAT;
}

static bool I2C1_IsData(void)
{
    return (SSP1STATbits.D_nA);
}

static bool I2C1_IsAddr(void)
{
    return !(SSP1STATbits.D_nA);
}

static bool I2C1_IsRxBufFull(void)
{
    return SSP1STATbits.BF;
}

static inline void I2C1_InterruptClear(void)
{
    PIR5bits.SSP1IF = 0;
}

static inline void I2C1_ErrorInterruptClear(void)
{
    PIR5bits.BCL1IF = 0;
}

static inline void I2C1_StatusFlagsClear(void)
{
    SSP1CON1bits.WCOL = 0;
    SSP1CON1bits.SSPOV = 0;
}