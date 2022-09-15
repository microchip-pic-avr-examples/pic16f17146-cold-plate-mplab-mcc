#ifndef ENCODERCONTROL_H
#define	ENCODERCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system/system.h"
#include "UI.h"
#include <stdbool.h>

typedef enum { BLUE, ORANGE, PURPLE, OFF } EncoderLEDState;
    
EncoderLEDState encoderControl_getLEDState(void);
void encoderControl_setLEDState(EncoderLEDState new_state);
bool encoderControl_getBreatheStatus(void);
void encoderControl_setBreatheStatus(bool status);

int16_t encoderControl_getMoves(void);
void encoderControl_updateColor(void);
void encoderControl_IncrementPWM(void);
void encoderControl_breatheLED(void);
void encoderControl_updateLEDs(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ENCODERCONTROL_H */

