#include "utility.h"

#include "mcc_generated_files/system/system.h"
#include "settings.h"
#include "config.h"
#include "compactPrint.h"

#include <xc.h>
#include <stdint.h>

uint16_t DIA_readValue(uint16_t address)
{
    //Load NVMADR with address of the word
    NVMADRH = (uint8_t) (address >> 8);
    NVMADRL = (uint8_t) address;

    //Access DIA Memory
    NVMCON1bits.NVMREGS = 1;
    
    //Initiate Read
    NVMCON1bits.RD = 1;      

    return ((uint16_t) ((NVMDATH << 8) | NVMDATL));
}

//Prints the Reset Registers to the UART
void System_printResetRegisters(void)
{
#ifdef DEBUG_PRINT
#ifdef DEBUG_RAW_VALUES
    compactPrint_sendErrorCode("PCON0: ", PCON0);
    compactPrint_sendErrorCode("PCON1: ", PCON1);
#endif
#endif
    
    //Clear Values
    PCON0 = 0x00;
    PCON1 = 0x00;
}

//Enables the WWDT
void WWDT_start(void)
{
    WWDT_reset();
    WDTCON0bits.WDTSEN = 0b1;
}

//Stops the WWDT
void WWDT_stop(void)
{
    WDTCON0bits.WDTSEN = 0b0;
}

//Arms a WWDT Reset
void WWDT_armReset(void)
{
    //Required to arm WWDT
    volatile uint8_t t = WDTCON0;
}

//Resets the WWDT
void WWDT_reset(void)
{
    asm("CLRWDT");
}

int8_t CtoF(int8_t celsius){
    if(celsius > 53){ // F overflows above this
        return 127;
    }
    return (int8_t)((celsius * 9.0/5.0)+ 32);
}

int8_t dispTemp(int8_t temp){
    return (settings_getSetting(SETTINGS_TEMP_UNIT) == 'C') ? temp : CtoF(temp);
}