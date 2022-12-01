#ifndef ENCODERCONTROL_H
#define	ENCODERCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system/system.h"
#include "UI.h"
#include <stdbool.h>
   
typedef enum { BLUE, ORANGE, PURPLE, OFF } EncoderLEDState;

int16_t encoderControl_getMoves(void);
void encoderControl_updateLEDs(void);
void encoderControl_setColor(EncoderLEDState color);
void encoderControl_setLEDValue(uint16_t orange, uint16_t blue);
void encoderControl_breatheLED(EncoderLEDState color);

#ifdef	__cplusplus
}
#endif

#endif	/* ENCODERCONTROL_H */

