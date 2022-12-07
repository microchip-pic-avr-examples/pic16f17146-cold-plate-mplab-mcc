#ifndef NTC_ROM_H
#define	NTC_ROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    /*
     * This is a ROM file for the NTC Thermistor P/N USP7765 from Littelfuse Inc.
     * Modified based on our measured values in system
     * 
     * Starting Position is -24C (lowest reading possible is -23C)
     * Ending Position is 104C (highest reading possible 103C)
     * 
     * Top Resistance is 27k
     * 
     * Note: First and last elements are not used by the search algorithm
     * 
     * Assumes VREF = 4.096V
     */

    const uint16_t NTC_values[] = {
    3507, 3464, 3420, 3376, 3330, 3284, 3238, 3191, 3143, 3095, 3047, 2998, 2948, 2898, 2848, 2798, 
    2747, 2696, 2645, 2594, 2543, 2492, 2441, 2389, 2338, 2287, 2237, 2186, 2136, 2086, 2036, 1987, 
    1938, 1889, 1841, 1794, 1747, 1701, 1655, 1610, 1566, 1522, 1479, 1436, 1395, 1354, 1314, 1275, 
    1236, 1198, 1161, 1125, 1090, 1055, 1022, 989, 957, 925, 895, 865, 836, 808, 780, 754, 
    728, 703, 678, 655, 632, 609, 588, 567, 547, 527, 508, 490, 472, 455, 438, 422, 
    406, 391, 377, 363, 349, 336, 323, 311, 299, 288, 277, 267, 256, 247, 237, 228, 
    219, 211, 203, 195, 187, 180, 173, 166, 160, 154, 148, 142, 136, 131, 126, 121, 
    116, 112, 107, 103, 99, 95, 91, 88, 84, 81, 78, 75, 72, 69, 66, 64, 61 };
     
//Temperatures are in C
#define NTC_START_TEMP -24
#define NTC_STOP_TEMP 104

//How many elements can be accessed in the array (note: 1 extra element is in the array)
#define NTC_VALUE_SIZE (NTC_STOP_TEMP - NTC_START_TEMP)    
        
    //Returns the nearest temperature to the input value. Returns INT8_MIN / INT8_MAX if out of range
    //Executes in O(log(NTC_VALUE_SIZE)) time
    int8_t NTC_ROM_search(uint16_t meas);
    
#ifdef	__cplusplus
}
#endif

#endif	/* NTC_ROM_H */

