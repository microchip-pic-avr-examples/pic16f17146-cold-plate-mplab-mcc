#ifndef TESTING_H
#define	TESTING_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Software Test Pattern for the NTC ROM Search Algorithm
    void TEST_NTC_ROM(void);
    
    //Software Test Pattern for Current -> DAC settings
    void TEST_DAC_Calc(void);
    
    //Software Test Pattern for Compact Print API
    void TEST_compactPrint(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TESTING_H */

