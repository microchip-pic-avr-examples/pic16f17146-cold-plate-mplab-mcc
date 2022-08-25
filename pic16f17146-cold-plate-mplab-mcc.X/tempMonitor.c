#include "tempMonitor.h"
#include "mcc_generated_files/system/system.h"
#include "config.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "utility.h"
#include "NTC_ROM.h"

static volatile int8_t coldTemp = INT8_MIN, hotTemp = INT8_MAX, intTemp = INT8_MAX;

//DIA Fields from the Device
static int16_t TS_GAIN = 0, TS_OFFSET = 0;
static uint16_t TS_90C = 0;

const int8_t testGain __at(0x3EF0) = 1;
const int8_t testOffset __at(0x3EF1) = 2;
const uint8_t test90C __at(0x3EF2) = 3;

//Last Measurement
enum currentMeasurement{
    SAMPLE_IDLE = 0, SAMPLE_COLD, SAMPLE_HOT, SAMPLE_INT
};

//State Machine for Measurement
enum measurementState {
    MEAS_COLD, MEAS_HOT, MEAS_INT
};

static volatile enum currentMeasurement sampleState = SAMPLE_IDLE;
static enum measurementState measState = MEAS_COLD;

//Initializes the Temperature Monitors
void tempMonitor_init(void)
{
    TS_GAIN = (int16_t) DIA_readValue(DIA_TSHR1);
    TS_90C = (uint16_t) DIA_readValue(DIA_TSHR2);
    TS_OFFSET = (int16_t) DIA_readValue(DIA_TSHR3);
    
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
    
#ifdef DEBUG_PRINT
    //Print Values
    printf("TS_GAIN = 0x%x, TS_90C = 0x%x, TS_OFFSET = 0x%x\r\n", TS_GAIN, TS_90C, TS_OFFSET);
#endif
    
}

//Runs a state machine to measure temperature
void tempMonitor_runStateMachine(void)
{
    switch (measState)
    {
        case MEAS_COLD:
        {
            tempMonitor_sampleCold();
            measState = MEAS_HOT;
            break;
        }
        case MEAS_HOT:
        {
            tempMonitor_sampleHot();
            measState = MEAS_INT;
            break;
        }
        case MEAS_INT:
        {
            tempMonitor_sampleIntTemp();
            measState = MEAS_COLD;
            break;
        }
        default:
        {
            
        }
    }
}

//Starts a temperature conversion for the Cold Plate NTC
void tempMonitor_sampleCold(void)
{
    //Select 4.096V Reference
    FVRCONbits.ADFVR = 0b11;
    
    //~10us per bit
    ADACQ = 100;
    
    //RA2 - 0b000010
    ADCC_StartConversion(0b000010);
    
    //Update State
    sampleState = SAMPLE_COLD;
}

//Starts a temperature conversion for the heatsink NTC
void tempMonitor_sampleHot(void)
{
    //Select 4.096V Reference
    FVRCONbits.ADFVR = 0b11;
    
    //~10us per bit
    ADACQ = 100;
    
    //RC0 - 0b010000
    ADCC_StartConversion(0b010000);
    
    //Update State
    sampleState = SAMPLE_HOT;
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
    
    //Update State
    sampleState = SAMPLE_INT;
    
}

//Loads results from the ADC. Results must be ready
void tempMonitor_loadResults(void)
{
    uint16_t ADCvalue = ADCC_GetFilterValue();
    
    switch(sampleState)
    {
        case SAMPLE_COLD:
        {
            coldTemp = NTC_ROM_search(ADCvalue);
            break;
        }
        case SAMPLE_HOT:
        {
            hotTemp = NTC_ROM_search(ADCvalue);
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
            //Not a temperature value
        }
    }
    
    sampleState = SAMPLE_IDLE;
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