#ifndef TEMPCONTROL_H
#define	TEMPCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    typedef enum {
        ERROR = -1, IDLE = 0, STARTING, TESTING, RUNNING, AT_TEMP
    } tempControl_state;
    
    //Initializes the Peltier Control Systems
    void tempControl_init(void);
    
    //Starts the Peltier Regulator
    void tempControl_start(void);
    
    //Stops the Peltier Regulator
    void tempControl_stop(void);
    
    //Returns the last reading from the cold plate in Celsius
    int8_t tempControl_getLastColdTemp(void);
    
    //Returns the last reading from the heatsink in Celsius
    int8_t tempControl_getLastHotTemp(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TEMPCONTROL_H */

