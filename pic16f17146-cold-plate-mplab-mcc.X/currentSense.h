#ifndef CURRENTSENSE_H
#define	CURRENTSENSE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Init Current Sense System
    void currentSense_init(void);
    
    //Runs current sense - self calibration
    //Blocking Code
    void currentSense_selfCalibrate(void);
    

#ifdef	__cplusplus
}
#endif

#endif	/* CURRENTSENSE_H */

