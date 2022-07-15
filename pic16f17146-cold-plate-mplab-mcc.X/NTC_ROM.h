#ifndef NTC_ROM_H
#define	NTC_ROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    /*
     * This is a ROM file for the NTC Thermistor P/N USP7765 from Littelfuse Inc.
     * 
     * Starting Position is -24C (lowest reading possible is -23C)
     * Ending Position is 104C (highest reading possible 103C)
     * 
     * Top Resistance is 27k
     */

    const uint16_t NTC_values[] = {  4099, 4054, 4008, 3961, 3912, 3862, 3811, 3758, 3704, 3649, 3593,
    3537, 3479, 3420, 3360, 3300, 3239, 3177, 3115, 3053, 2990, 2927, 2863, 2800,
    2737, 2674, 2611, 2548, 2485, 2423, 2362, 2301, 2240, 2181, 2122, 2063, 2006,
    1949, 1894, 1839, 1786, 1733, 1681, 1631, 1582, 1533, 1486, 1440, 1395, 1351,
    1309, 1267, 1227, 1187, 1149, 1112, 1076, 1041, 1007, 974, 942, 911, 881, 852,
    824, 797, 770, 745, 720, 696, 673, 651, 629, 609, 589, 569, 550, 532, 515, 498,
    482, 466, 451, 436, 422, 408, 395, 382, 370, 358, 347, 335, 325, 315, 305, 295,
    286, 277, 268, 260, 252, 244, 236, 229, 222, 215, 209, 203, 196, 191, 185, 179,
    174, 169, 164, 159, 155, 150, 146, 142, 138, 134, 130, 126, 123, 119, 116, 113, 110 };
    
//Temperatures are in C
#define NTC_START_TEMP -24
#define NTC_STOP_TEMP 104

//How many elements are in the array
#define NTC_VALUE_SIZE (NTC_STOP_TEMP - NTC_START_TEMP)    
    
    //Returns the nearest temperature to the input value. Returns INT8_MIN / INT8_MAX if out of range
    //Executes in O(log(NTC_VALUE_SIZE)) time
    int8_t NTC_ROM_search(uint16_t meas);
    
#ifdef	__cplusplus
}
#endif

#endif	/* NTC_ROM_H */

