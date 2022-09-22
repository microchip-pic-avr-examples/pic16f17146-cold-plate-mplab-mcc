#ifndef FANCONTROL_H
#define	FANCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //Init Fan Speed Control
    void fanControl_init(void);

    //Start Cooling Fans
    void fanControl_start(void);

    //Stop Cooling Fans
    void fanControl_stop(void);
    
    //Sets the fan speed based on the heatsink temperature
    void fanControl_updateSpeedFromTemp(int8_t hTemp);
    
    //Returns the RPM of Fan 1
    uint16_t fanControl_getFan1RPM(void);
    
    //Returns the RPM of Fan 2
    uint16_t fanControl_getFan2RPM(void);
    
    //Call this function once per second to update RPM
    void fanControl_timerCallback(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* FANCONTROL_H */

