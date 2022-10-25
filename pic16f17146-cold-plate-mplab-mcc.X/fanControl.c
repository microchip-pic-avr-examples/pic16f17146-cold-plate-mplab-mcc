#include "fanControl.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/pwm/pwm2_16bit.h"
#include "config.h"
#include <xc.h>

#include <stdint.h>

//Last RPM of the cooling fans
static volatile uint16_t fan1RPM = 0, fan2RPM = 0;

//Last Values in Timer 2 / Timer 4
static volatile uint8_t lastTimer2 = 0, lastTimer4 = 0;

//Init Fan Speed Control
void fanControl_init(void)
{    
    //Fan 1 RPM Counter
    Timer2_Start();
    
    //Fan 2 RPM Counter
    Timer4_Start();
    
    FAN_PWM_Enable();
}

//Start Cooling Fans
void fanControl_start(void)
{
    //Enable Fan PWM
    FAN_PWM_Enable();
}

//Stop Cooling Fans
void fanControl_stop(void)
{
    //Disable Fan PWM
    FAN_PWM_Disable();
}

//Sets the fan speed based on the heatsink temperature
void fanControl_updateSpeedFromTemp(int8_t hTemp)
{
    //320 = 25% speed
    
    if (hTemp >= HEATSINK_TEMP_FAN_MAX)
    {
        //100% Fan Speed
        FAN_PWM_SetSlice1Output1DutyCycleRegister(0xFFFF);
    }
    else if (hTemp <= HEATSINK_TEMP_FAN_MIN)
    {
        //Below min temperature, low speed
        FAN_PWM_SetSlice1Output1DutyCycleRegister(320);
    }
    else
    {
        uint16_t fanSpeed = 320 + (HEATSINK_TEMP_SLOPE * (hTemp - HEATSINK_TEMP_FAN_MIN));
        FAN_PWM_SetSlice1Output1DutyCycleRegister(fanSpeed);
    }
    
    //100%
    
    FAN_PWM_LoadBufferRegisters();
}

//Returns the RPM of Fan 1
uint16_t fanControl_getFan1RPM(void)
{
    return fan1RPM;
}

//Returns the RPM of Fan 2
uint16_t fanControl_getFan2RPM(void)
{
    return fan2RPM;
}

//Call this function to update RPM
void fanControl_timerCallback(void)
{
    //Note: From Noctua - 2 Pulses per RPM
    
    uint8_t cTimer2, cTimer4;
    
    //Read Current Pulse Counts
    cTimer2 = Timer2_Read();
    cTimer4 = Timer4_Read();
    
    //Compute RPM from number of pulses since last time
    if (cTimer2 < lastTimer2)
    {
        //Overflow!
        fan1RPM = ((0xFF - lastTimer2) + cTimer2 + 1) * 30;
    }
    else
    {
        //No Overflow
        fan1RPM = (cTimer2 - lastTimer2) * 30;
    }
    
    //Compute RPM from number of pulses since last time
    if (cTimer4 < lastTimer4)
    {
        //Overflow!
        fan2RPM = ((0xFF - lastTimer4) + cTimer4 + 1) * 30;
    }
    else
    {
        //No Overflow
        fan2RPM = (cTimer4 - lastTimer4) * 30;
    }
    
    //Update Last Counts
    lastTimer2 = cTimer2;
    lastTimer4 = cTimer4;
}