#include "tempMonitor.h"
#include "mcc_generated_files/adcc/adcc.h"
#include "mcc_generated_files/nvm/nvm.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

static int8_t coldTemp = INT8_MIN, hotTemp = INT8_MAX, intTemp = INT8_MAX;

//DIA Fields from the Device
static uint16_t TS_GAIN, TS_90C;
static uint8_t TS_OFFSET;

enum measurementState{
    MEASUREMENT_IDLE = 0, SAMPLE_COLD, SAMPLE_HOT, SAMPLE_INT
};

static volatile enum measurementState state = MEASUREMENT_IDLE;

//Initializes the Temperature Monitors
void tempMonitor_init(void)
{
    TS_GAIN = FLASH_Read(DIA_TSHR1);
    TS_90C = FLASH_Read(DIA_TSHR2);
    TS_OFFSET = (FLASH_Read(DIA_TSHR3) & 0xFF); //Note: Offset is 1 byte, not 2
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
    
    //Start ADCC Conversion
    ADCC_StartConversion(channel_Temp);
    
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
            int24_t buffer = (ADCvalue) * TS_GAIN;
            buffer = buffer / 256;
            buffer += TS_OFFSET;
            
            intTemp = buffer & 0xFF;
            
            break;
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
