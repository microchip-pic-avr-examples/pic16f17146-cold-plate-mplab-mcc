#include "encoderControl.h"


// Return total encoder moves since last poll
int16_t encoderControl_getMoves(void){
    static uint16_t oldTimer1 = 0;
    static uint16_t oldTimer3 = 0;
    
    uint16_t newTimer1, newTimer3, netTimer1, netTimer3;
    int16_t encoder;
    
    newTimer1 = Timer1_Read();
    newTimer3 = Timer3_Read();
    
    netTimer1 = 0;
    netTimer3 = 0;
    
    if(newTimer1 < oldTimer1){
        // Rollover occurred
        // Add an offset to the net value and clear the old value
        netTimer1 = 0xFFFF - oldTimer1;
        oldTimer1 = 0;
    }
    
     if(newTimer3 < oldTimer3){
        // Rollover occurred
        // Add an offset to the net value and clear the old value
        netTimer3 = 0xFFFF - oldTimer3;
        oldTimer3 = 0;
    }
    
    //Find the net change
    netTimer1 += newTimer1 - oldTimer1;
    netTimer3 += newTimer3 - oldTimer3;
    
    // Calculate the net encoder change
    encoder = (int16_t)(netTimer3 - netTimer1);
    
    oldTimer1 = newTimer1;
    oldTimer3 = newTimer3;
    
    return encoder;
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
    switch(UI_getState()){
        case STANDBY:
            encoderControl_setLEDState(PURPLE);
            breatheStatus = true;
            break;
        case ERROR:
            encoderControl_setLEDState(ORANGE);
            breatheStatus = false;
            break;
        case MENU:
            if(!UI_isRunning()){
                encoderControl_setLEDState(PURPLE);
                breatheStatus = false;
            } else { // if in running menu
                // TODO: set depending if at temp
                encoderControl_setLEDState(PURPLE);
                breatheStatus = false;
            }
            break;
        case RUNNING:
            // TODO: check if at temp
            encoderControl_setLEDState(BLUE);
            breatheStatus = false;
            break;
    }
}


// set encoder LED colors
void encoderControl_updateColor(void){
    switch(LEDState){
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
            LED_ERROR_SetLow();
            LED_STATUS_SetLow();
            break;
    }
}


// number of PWM increments (PWM functions scale to each intensity level is 10% of increments)
#define PWM_increments 20
static uint8_t PWM_intensity = 0; // value between 0 - PWM_increments


// PWM intensity between 0-PWM_increments
void encoderControl_PWM(void){
    static uint8_t duty_cycle = 0;
    if(duty_cycle < PWM_intensity){
        LED_ERROR_SetHigh();
        LED_STATUS_SetHigh();
    } else if(duty_cycle <= PWM_increments){
        LED_ERROR_SetLow();
        LED_STATUS_SetLow();
    } else{
        duty_cycle = 0;
    }
    duty_cycle++;
}

// if breathing, call every 10ms
void encoderControl_breatheLED(void){
    enum BREATHING_STATES {RAMPING_UP, PEAK, RAMPING_DOWN, BOTTOM};
    static enum BREATHING_STATES breathing_state = RAMPING_UP;
    static uint16_t counter = 0;
    
    switch(breathing_state){
        case RAMPING_UP: 
            if(counter >= 3){ // PWM 1% increase every 10ms
                PWM_intensity+=1;
                counter = 0;
            }
            if(PWM_intensity >= PWM_increments){ // when intensity is maxed out
                breathing_state = PEAK;
                counter = 0;
            }
            break;
        case PEAK: // wait 500ms before ramping down
            if(counter >= 50){
                breathing_state = RAMPING_DOWN;
                counter = 0;
            }
            break;
        case RAMPING_DOWN:
            if(counter >= 3){ // PWM 1% decrease every 10ms
                PWM_intensity-=1;
                counter = 0;
            }
            if(PWM_intensity <= 0){
                breathing_state = BOTTOM;
                counter = 0;
            }
            break;
        case BOTTOM:
            if(counter >= 50){ // wait 50 ms before restarting cycle
                breathing_state = RAMPING_UP;
                counter = 0;
            }
            break;
    }
    counter++;
}