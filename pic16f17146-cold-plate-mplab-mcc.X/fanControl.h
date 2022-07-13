#ifndef FANCONTROL_H
#define	FANCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
//Number of times pulse count is read per second
#define FAN_UPDATE_CALLBACKS_PER_SEC 100
    
    //Init Fan Speed Control
    void fanControl_init(void);

    //Start Cooling Fans
    void fanControl_start(void);

    //Stop Cooling Fans
    void fanControl_stop(void);
    
    //Returns the RPM of Fan 1
    uint16_t fanControl_getFan1RPM(void);
    
    //Returns the RPM of Fan 2
    uint16_t fanControl_getFan2RPM(void);
    
    //Every 10ms, call this function to update RPM
    void fanControl_timerCallback(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* FANCONTROL_H */

