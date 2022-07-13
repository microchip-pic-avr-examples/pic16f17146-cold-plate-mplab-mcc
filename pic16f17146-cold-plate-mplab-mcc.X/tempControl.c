#include "tempControl.h"
#include "mcc_generated_files/pwm/pwm2_16bit.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//Is the current loop enabled?
static bool tempControlActive = false;

//Last Measured Temperatures
static int8_t lastCold = -127, lastHot = 127;

//Initializes the Peltier Control Systems
void tempControl_init(void)
{
    //Enable Cooling Fans
    FAN_PWM_Enable();
}

//Starts the Peltier Regulator
void tempControl_start(void)
{
    tempControlActive = true;
}

//Stops the Peltier Regulator
void tempControl_stop(void)
{
    tempControlActive = false;
}

//Returns the last reading from the cold plate in Celsius
int8_t tempControl_getLastColdTemp(void)
{
    return lastCold;
}

//Returns the last reading from the heatsink in Celsius
int8_t tempControl_getLastHotTemp(void)
{
    return lastHot;
}

