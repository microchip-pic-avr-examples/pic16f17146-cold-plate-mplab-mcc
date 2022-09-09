#include "encoderControl.h"


static volatile int16_t encoderMoves = 0;


// Return total encoder moves since last poll
int16_t encoderControl_getMoves(void){
    encoderControl_resetTimers();
    return encoderMoves;
}


// calculate difference in timers to see total moves since last call & reset timers
void encoderControl_resetTimers(void){
    encoderMoves = (int16_t)Timer3_Read() - (int16_t)Timer1_Read(); // + if right, - if left
    Timer1_Write(0);
    Timer3_Write(0);
}

EncoderLEDState LEDState = OFF; // BLUE, ORANGE, BOTH, or OFF
bool breatheStatus = false; // whether to breathe the LED

// LED color getter
EncoderLEDState encoderControl_getLEDState(void){
    return LEDState;
}

// LED color setter
void encoderControl_setLEDState(EncoderLEDState new_state){
    LEDState = new_state;
}

bool encoderControl_getBreatheStatus(void){
    return breatheStatus;
}

void encoderControl_setBreatheStatus(bool status){
    breatheStatus = status;
}


void encoderControl_updateLEDs(void){
    if(UI_getState() == STANDBY){ // Standby
        encoderControl_setLEDState(PURPLE);
        breatheStatus = true;
    } else if(UI_getState() == ERROR){ // Error
        encoderControl_setLEDState(ORANGE);
        breatheStatus = false;
    } else if (!UI_isRunning()){ // Not in standby, not running (in menu))
        encoderControl_setLEDState(PURPLE);
        breatheStatus = false;
    } else if(UI_isRunning()){ // Is Running
        encoderControl_setLEDState(BLUE);
        // TODO;
        // breathe when cooling
        
        // solid at temp
        
    }
    if(!breatheStatus){
    encoderControl_updateColor();
    }
}


// set encoder LED colors
void encoderControl_updateColor(void){
    switch(LEDState){
//        LED_ERROR_SetLow();
//        LED_STATUS_SetLow();
        case ORANGE:
            LED_ERROR_SetHigh();
            LED_STATUS_SetLow();
            break;
        case BLUE:
            LED_ERROR_SetLow();
            LED_STATUS_SetHigh();
            break;
        case PURPLE:
            LED_ERROR_SetHigh();
            LED_STATUS_SetHigh();
            break;
        case OFF: 
        default:
            LED_ERROR_SetLow();
            LED_STATUS_SetLow();
            break;
    }
}


// number of PWM increments (PWM functions scale to each intensity level is 10% of increments)
#define PWM_increments 20
static uint8_t PWM_intensity = 0; // value between 0 - PWM_increments


// PWM intensity between 0-PWM_increments
void encoderControl_IncrementPWM(void){
    static uint8_t duty_cycle = 0;
    if(duty_cycle < PWM_intensity){
        encoderControl_setLEDState(PURPLE);
    } else if(duty_cycle <= PWM_increments){
        encoderControl_setLEDState(OFF);
    } else{
        duty_cycle = 0;
    }
    duty_cycle++;
    encoderControl_updateColor(); // set color to current state
}

// if breathing, call every 10ms
void encoderControl_breatheLED(void){
//    enum BREATHING_STATES {RAMPING_UP, PEAK, RAMPING_DOWN, BOTTOM};
//    static enum BREATHING_STATES breathing_state = RAMPING_UP;
//    static uint16_t counter = 0;
//    
//    switch(breathing_state){
//        case RAMPING_UP: 
//            if(counter >= 3){ // PWM 1% increase every 10ms
//                PWM_intensity+=1;
//                counter = 0;
//            }
//            if(PWM_intensity >= PWM_increments){ // when intensity is maxed out
//                breathing_state = PEAK;
//                counter = 0;
//            }
//            break;
//        case PEAK: // wait 500ms before ramping down
//            if(counter >= 50){
//                breathing_state = RAMPING_DOWN;
//                counter = 0;
//            }
//            break;
//        case RAMPING_DOWN:
//            if(counter >= 3){ // PWM 1% decrease every 10ms
//                PWM_intensity-=1;
//                counter = 0;
//            }
//            if(PWM_intensity <= 0){
//                breathing_state = BOTTOM;
//                counter = 0;
//            }
//            break;
//        case BOTTOM:
//            if(counter >= 50){ // wait 50 ms before restarting cycle
//                breathing_state = RAMPING_UP;
//                counter = 0;
//            }
//            break;
//    }
//    counter++;
    PWM_intensity=0;
}