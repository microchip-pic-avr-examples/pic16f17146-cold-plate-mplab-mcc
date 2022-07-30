#ifndef UTILITY_H
#define	UTILITY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //Read a value from the DIA fields in the MCU
    uint16_t DIA_readValue(uint16_t address);
    
    //Prints the Reset Registers to the UART
    void System_printResetRegisters(void);
    
    //Enables the WWDT
    void WWDT_start(void);
    
    //Stops the WWDT
    void WWDT_stop(void);
    
    //Arms a WWDT Reset
    //Should not be called immediately before WWDT_reset
    void WWDT_armReset(void);

    //Resets the WWDT
    void WWDT_reset(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* UTILITY_H */

