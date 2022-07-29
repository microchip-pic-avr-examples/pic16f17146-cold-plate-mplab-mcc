#include "tempMonitor.h"
#include "mcc_generated_files/system/system.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

static volatile int8_t coldTemp = INT8_MIN, hotTemp = INT8_MAX, intTemp = INT8_MAX;

//DIA Fields from the Device
static int16_t TS_GAIN = 0, TS_OFFSET = 0;
static uint16_t TS_90C = 0;

const int8_t testGain __at(0x3EF0) = 1;
const int8_t testOffset __at(0x3EF1) = 2;
const uint8_t test90C __at(0x3EF2) = 3;

enum measurementState{
    MEASUREMENT_IDLE = 0, SAMPLE_COLD, SAMPLE_HOT, SAMPLE_INT
};

static volatile enum measurementState state = MEASUREMENT_IDLE;

//Initializes the Temperature Monitors
void tempMonitor_init(void)
{
    TS_GAIN = (int16_t) FLASH_Read(DIA_TSHR1);
    TS_90C = (uint16_t) FLASH_Read(DIA_TSHR2);
    TS_OFFSET = (int16_t) FLASH_Read(DIA_TSHR3);
    
    if(TS_GAIN & 0x2000)
    {
        //Negative Value, sign extend
        TS_GAIN |= 0xC000;
    }

    
    if(TS_OFFSET & 0x2000)
    {
        //Negative Value, sign extend
        TS_OFFSET |= 0xC000;
    }
//    printf("DIA_TSHR1 = 0x%x, DIA_TSHR2 = 0x%x, DIA_TSHR3 = 0x%x\r\n", DIA_TSHR1, DIA_TSHR2, DIA_TSHR3);
    printf("TS_GAIN = 0x%x, TS_90C = 0x%x, TS_OFFSET = 0x%x\r\n", TS_GAIN, TS_90C, TS_OFFSET);
}

//Starts a temperature conversion for the Cold Plate NTC
void tempMonitor_sampleCold(void)
{
    
}

//Starts a temperature conversion for the heatsink NTC
void tempMonitor_sampleHot(void)
{
    
}

//Starts a temperature conversion using the internal temp sensor
void tempMonitor_sampleIntTemp(void)
{
    //25us for FVR, 25us for TEMP
    
    //Select 2.048V Reference
    FVRCONbits.ADFVR = 0b10;
    
    //500kHz ADCRC
    //2us per bit
    ADACQ = 25;
    
    //Clear Math bit
    ADSTATbits.MATH = 0b0;
    
    //Start ADCC Conversion
    ADCC_StartConversion(channel_Temp);
    
    //Update State
    state = SAMPLE_INT;
    
}

//Loads results from the ADC. Results must be ready
void tempMonitor_loadResults(void)
{
    uint16_t ADCvalue = ADCC_GetFilterValue();
    
    switch(state)
    {
        case SAMPLE_COLD:
        {
            break;
        }
        case SAMPLE_HOT:
        {
            break;
        }
        case SAMPLE_INT:
        {                        
            int24_t buffer = (int24_t) (ADCvalue) * TS_GAIN;
            
            //Add 128 to ensure good rounding
            buffer = (buffer + 128) / 256;
            
            buffer += TS_OFFSET;
            buffer /= 10;
            intTemp = buffer & 0xFF;
            
            break;
        }
        default:
        {
            
        }
    }
    
    state = MEASUREMENT_IDLE;
}

//Returns the last cold plate temperature
int8_t tempMonitor_getLastColdTemp(void)
{
    return coldTemp;
}

//Returns the last heatsink temperature
int8_t tempMonitor_getLastHotTemp(void)
{
    return hotTemp;
}

//Returns the last internal temperature
int8_t tempMonitor_getLastIntTemp(void)
{
    return intTemp;
}