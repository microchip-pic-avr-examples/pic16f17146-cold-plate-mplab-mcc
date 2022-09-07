#include "testing.h"

#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "NTC_ROM.h"
#include "config.h"

#define NTC_ROM_TEST_SIZE 10

void TEST_NTC_ROM(void)
{
    //Test the NTC ROM Search Algorithms
    
#ifdef DEBUG_PRINT
    printf("Running NTC ROM Test Pattern...\r\n");
#endif
    uint16_t testValues[NTC_ROM_TEST_SIZE];
    
    testValues[0] = 824;    //40C Exactly (starting point)
    testValues[1] = 1227;   //28C Exactly
    testValues[2] = 113;    //103C Exactly
    testValues[3] = 4054;   //-23C Exactly
    
    testValues[4] = 4100;   //Should Return -128C (Out of Range, Low)
    testValues[5] = 100;    //Should Return 127C (Out of Range, High)
    
    testValues[6] = 1355;   //Near 25C - should be within a degree
    testValues[7] = 390;    //Near 63C - should be within a degree
    testValues[8] = 3340;   //Near -10C - should be within a degree
    testValues[9] = 165;    //Near 90C - should be within a degree
    
    int8_t tempOut;
    
    for (uint8_t i = 0; i < NTC_ROM_TEST_SIZE; i++)
    {
        tempOut = NTC_ROM_search(testValues[i]);
#ifdef DEBUG_PRINT
        printf("Test %u - Temperature at value %u: %dC\r\n", i, testValues[i], tempOut);
#endif

    }
}

//Software Test Pattern for Current -> DAC settings
void TEST_DAC_Calc(void)
{
    uint8_t dacCode;
#ifdef DEBUG_PRINT
    printf("Running DAC Computation Tests...\r\n");
#endif
    
    uint8_t testValues[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    
    for (uint8_t i = 0; i < 10; i++)
    {
       //Same formula!
       dacCode = floorf(DAC_FORMULA_CONSTANT * 8.0 * testValues[i]);
#ifdef DEBUG_PRINT
        printf("Test %u - DAC set for input %u: %dC\r\n", i, testValues[i], dacCode);
#endif
    }
}
