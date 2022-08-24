#include "NTC_ROM.h"

#include <stdint.h>

//Returns the nearest temperature to the input value. Returns INT8_MIN / INT8_MAX if out of range
//Executes in O(log(NTC_VALUE_SIZE)) time
int8_t NTC_ROM_search(uint16_t meas)
{
    //Return Range Error (too cold)
    if (meas >= NTC_values[0])
    {
        return INT8_MIN;
    }
    
    //Return Range Error (too hot)
    if (meas <= NTC_values[NTC_VALUE_SIZE])
    {
        return INT8_MAX;
    }
    
    //Current Address to Search
    uint8_t index = NTC_VALUE_SIZE >> 1;
    
    //Index Delta (how many entries to go up or down)
    uint8_t delta = NTC_VALUE_SIZE >> 2;
    
    //Current ROM value to compare with
    uint16_t ROMvalue;
    
    while (delta != 0)
    {
        ROMvalue = NTC_values[index];
        if (ROMvalue == meas)
        {
            //Perfect Match!
            delta = 0;
        }
        else if (ROMvalue > meas)
        {
            //Need to go lower (index Up)
            index += delta;
        }
        else
        {
            //Need to go higher (Index Down)
            index -= delta;
        }
        
        //Half the Delta
        delta >>= 1;
    }
    
    //Index is the current temp, plus/minus an offset
    return (index + NTC_START_TEMP);
}