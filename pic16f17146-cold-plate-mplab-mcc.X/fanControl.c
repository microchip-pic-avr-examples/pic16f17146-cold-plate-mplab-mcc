#include "fanControl.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/pwm/pwm2_16bit.h"
#include <xc.h>

#include <stdint.h>

//Last RPM of the cooling fans
static volatile uint16_t fan1RPM = 0, fan2RPM = 0;

//Last Values in Timer 2 / Timer 4
static volatile uint8_t lastTimer2 = 0, lastTimer4 = 0;

//Init Fan Speed Control
void fanControl_init(void)
{
    //Assign Timer 2 Input (RA4)
    T2INPPS = 0b000100;
    
    //Assign Timer 4 Input (RA5)
    T4INPPS = 0b000101;
    
    //Fan 1 RPM Counter
    Timer2_Start();
    
    //Fan 2 RPM Counter
    Timer4_Start();
}

//Start Cooling Fans
void fanControl_start(void)
{
    //Enable Fan PWM
    //FAN_PWM_Enable();
}

//Stop Cooling Fans
void fanControl_stop(void)
{
    //Disable Fan PWM
    //FAN_PWM_Disable();
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

//Every 10ms, call this function to update RPM
void fanControl_timerCallback(void)
{
    uint8_t cTimer2, cTimer4;
    
    //Read Current Pulse Counts
    cTimer2 = Timer2_Read();
    cTimer4 = lastTimer2;
    
    //Compute RPM from number of pulses since last time
    if (cTimer2 < lastTimer2)
    {
        //Overflow!
        fan1RPM = ((0xFF - lastTimer2) + cTimer2 + 1) * 60;
    }
    else
    {
        //No Overflow
        fan1RPM = (cTimer2 - lastTimer2) * 60;
    }
    
    //Compute RPM from number of pulses since last time
    if (cTimer4 < lastTimer4)
    {
        //Overflow!
        fan2RPM = FAN_SCALING_VALUE * ((0xFF - lastTimer4) + cTimer4 + 1);
    }
    else
    {
        //No Overflow
        fan2RPM = FAN_SCALING_VALUE * (cTimer4 - lastTimer4);
    }
    
    //Update Last Counts
    lastTimer2 = cTimer2;
    lastTimer4 = cTimer4;
}