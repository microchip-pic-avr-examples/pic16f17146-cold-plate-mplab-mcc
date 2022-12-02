#include "measurements.h"
#include "mcc_generated_files/system/system.h"
#include "config.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "utility.h"
#include "NTC_ROM.h"
#include "currentSense.h"

static volatile int8_t coldTemp = INT8_MIN, hotTemp = INT8_MAX, intTemp = INT8_MAX;
static volatile uint16_t coldADC, hotADC, intADC, currentADC;
static volatile uint8_t peltierCurrent = 0;

//DIA Fields from the Device
static int16_t TS_GAIN = 0, TS_OFFSET = 0;
static uint16_t TS_90C = 0;

const int8_t testGain __at(0x3EF0) = 1;
const int8_t testOffset __at(0x3EF1) = 2;
const uint8_t test90C __at(0x3EF2) = 3;

//Last Measurement
enum currentMeasurement{
    SAMPLE_IDLE = 0, SAMPLE_COLD, SAMPLE_HOT, SAMPLE_INT, SAMPLE_PELTIER
};

//State Machine for Measurement
enum measurementState {
    MEAS_COLD, MEAS_HOT, MEAS_INT, MEAS_PELTIER
};

static volatile enum currentMeasurement sampleState = SAMPLE_IDLE;
static enum measurementState measState = MEAS_COLD;

//Initializes the Temperature Monitors
void Measurements_init(void)
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
}

//Runs a state machine to measure temperature
void Measurements_runStateMachine(void)
{
    switch (measState)
    {
        case MEAS_COLD:
        {
            Measurements_sampleCold();
            measState = MEAS_HOT;
            break;
        }
        case MEAS_HOT:
        {
            Measurements_sampleHot();
            measState = MEAS_INT;
            break;
        }
        case MEAS_INT:
        {
            Measurements_sampleIntTemp();
            measState = MEAS_PELTIER;
            break;
        }
        case MEAS_PELTIER:
        {
            Measurements_sampleCurrent();
            measState = MEAS_COLD;
            break;
        }
        default:
        {
            
        }
    }
}

//Starts a temperature conversion for the Cold Plate NTC
void Measurements_sampleCold(void)
{
    //Select 4.096V Reference
    FVRCONbits.ADFVR = 0b11;
    
    //~10us per bit
    ADACQ = 100;
    
    //RA2 - 0b000010
    ADCC_StartConversion(NTC_COLD_SENSE_IN);
    
    //Update State
    sampleState = SAMPLE_COLD;
}

//Starts a temperature conversion for the heatsink NTC
void Measurements_sampleHot(void)
{
    //Select 4.096V Reference
    FVRCONbits.ADFVR = 0b11;
    
    //~10us per bit
    ADACQ = 100;
    
    //RC0 - 0b010000
    ADCC_StartConversion(NTC_HOT_SENSE_IN);
    
    //Update State
    sampleState = SAMPLE_HOT;
}

//Starts a temperature conversion using the internal temp sensor
void Measurements_sampleIntTemp(void)
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

//Measures current through the loop
void Measurements_sampleCurrent(void)
{
    //25us for FVR, 1us for OPAMP
    
    //Select 2.048V Reference
    FVRCONbits.ADFVR = 0b10;
    
    //500kHz ADCRC
    //2us per bit
    ADACQ = 15;
    
    //Start ADCC Conversion
    ADCC_StartConversion(channel_OPA1OUT);
    
    //Update State
    sampleState = SAMPLE_PELTIER;
}

//Loads results from the ADC. Results must be ready
void Measurements_loadResults(void)
{
    uint16_t ADCvalue = ADCC_GetFilterValue();
    
    switch(sampleState)
    {
        case SAMPLE_COLD:
        {
            coldADC = ADCvalue;
            coldTemp = NTC_ROM_search(ADCvalue);
            break;
        }
        case SAMPLE_HOT:
        {
            hotADC = ADCvalue;
            hotTemp = NTC_ROM_search(ADCvalue);
            break;
        }
        case SAMPLE_INT:
        {                        
            intADC = ADCvalue;
            int24_t buffer = (int24_t) (ADCvalue) * TS_GAIN;
            
            //Add 128 to ensure good rounding
            buffer = (buffer + 128) / 256;
            
            buffer += TS_OFFSET;
            buffer /= 10;
            intTemp = (int8_t)(buffer & 0xFF);
            
            break;
        }
        case SAMPLE_PELTIER:
        {
            currentADC = ADCvalue;
            switch (currentSense_getConfiguration())
            {
                case UNITY:
                    //50 mA per bit
                    peltierCurrent = ADCvalue >> 1;
                    break;
                case GAIN_2:
                    //25 mA per bit
                    peltierCurrent = ADCvalue >> 2;
                    break;
                case GAIN_4:
                    //12.5 mA per bit
                    peltierCurrent = ADCvalue >> 3;
                    break;
                case GAIN_8:
                    //6.25 mA per bit
                    peltierCurrent = ADCvalue >> 4;
                    break;
                case GAIN_16:
                    //3.125 mA per bit
                    peltierCurrent = ADCvalue >> 5;
                    break;
            }
            
            break;
        }
        default:
        {
            //Unknown
        }
    }
    
    sampleState = SAMPLE_IDLE;
}

//Returns the last cold plate temperature
int8_t Measurements_getLastColdTemp(void)
{
    return coldTemp;
}

uint16_t Measurements_getRawColdValue(void)
{
    return coldADC;
}

//Returns the last heatsink temperature
int8_t Measurements_getLastHotTemp(void)
{
    return hotTemp;
}

uint16_t Measurements_getRawHotValue(void)
{
    return hotADC;
}

//Returns the last internal temperature
int8_t Measurements_getLastIntTemp(void)
{
    return intTemp;
}

uint16_t Measurements_getRawIntValue(void)
{
    return intADC;
}

//Returns the last current through the loop
uint8_t Measurements_getLastCurrent(void)
{
    return peltierCurrent;
}

//Returns the raw current value from the ADC
uint16_t Measurements_getRawCurrentValue(void)
{
    return currentADC;
}