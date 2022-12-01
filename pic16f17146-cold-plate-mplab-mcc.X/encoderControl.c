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

// called every 10ms
void encoderControl_updateLEDs(void){
    switch(UI_getState()){
        case STANDBY:
            encoderControl_breatheLED(PURPLE);
            break;
        case ERROR:
            encoderControl_setColor(ORANGE);
            break;
        case MENU:
            if(!UI_isRunning()){
                encoderControl_setColor(PURPLE);
            } else { // If running
                if(!(peltierControl_getState() == PELTIER_STATE_AT_TEMP)){
                    encoderControl_breatheLED(BLUE);
                } else {
                    encoderControl_setColor(BLUE);
                }
            }
            break;
        case RUNNING:
            // PWM while cooling, Solid blue at temp
            if(!(peltierControl_getState() == PELTIER_STATE_AT_TEMP)){
                encoderControl_breatheLED(BLUE);
            } else {
                encoderControl_setColor(BLUE);
            }
            break;
    }
}

void encoderControl_setColor(EncoderLEDState color){
    switch(color){
        case BLUE:
            encoderControl_setLEDValue(65535, 0);
            break;
        case ORANGE:
            encoderControl_setLEDValue(0, 65535);
            break;
        case PURPLE:
            encoderControl_setLEDValue(65535, 65535);
            break;
        case OFF:
            encoderControl_setLEDValue(0, 0);
            break;
    }
}

// set encoder LED colors
void encoderControl_setLEDValue(uint16_t blue, uint16_t orange){
    LED_PWM_SetSlice1Output1DutyCycleRegister(blue);
    LED_PWM_SetSlice1Output2DutyCycleRegister(orange);
    LED_PWM_LoadBufferRegisters();
}

// number of PWM increments (PWM functions scale to each intensity level is 10% of increments)
#define PWM_MAX_VAL 200
#define PWM_increments 100


// if breathing, call every 10ms
void encoderControl_breatheLED(EncoderLEDState color){
    enum BREATHING_STATES {RAMPING_UP, PEAK, RAMPING_DOWN, BOTTOM};
    static enum BREATHING_STATES breathing_state = RAMPING_UP;
    static uint16_t delay_counter = 0;
    static uint8_t PWM_intensity = 0; // value between 0 - PWM_increments
    
    switch(breathing_state){
        case RAMPING_UP: 
            PWM_intensity+=1;
            encoderControl_setLEDValue((int)(PWM_MAX_VAL/PWM_increments) * PWM_intensity, (color == PURPLE) ? (int)(PWM_MAX_VAL/PWM_increments) * PWM_intensity : 0);
            if(PWM_intensity >= PWM_increments){ // when intensity is maxed out
                breathing_state = PEAK;
                delay_counter = 0;
            }
            break;
        case PEAK: // wait 500ms before ramping down
            if(delay_counter >= 50){
                breathing_state = RAMPING_DOWN;
                delay_counter = 0;
            }
            break;
        case RAMPING_DOWN:
            PWM_intensity-=1;
            encoderControl_setLEDValue((int)(PWM_MAX_VAL/PWM_increments) * PWM_intensity, (color == PURPLE) ? (int)(PWM_MAX_VAL/PWM_increments) * PWM_intensity : 0);

            if(PWM_intensity <= 0){
                breathing_state = BOTTOM;
                delay_counter = 0;
            }
            break;
        case BOTTOM:
            if(delay_counter >= 50){ // wait 50 ms before restarting cycle
                breathing_state = RAMPING_UP;
                delay_counter = 0;
            }
            break;
    }
    delay_counter++;
}