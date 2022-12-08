[![MCHP](images/microchip.png)](https://www.microchip.com)

# The Cold Plate

Packed with more functions than MCU pins, this cold plate demo can chill anything from a refreshing cool down to a powerful freeze, all controlled with the a single 20-pin, 8-bit PIC16F17146 microcontroller. As opposed a hot-plate, this plate is for cooling liquids or, if the power is increased, even keeping ice cream frozen. Traditionally, 8-bit MCU's are not used in complex applications such as this one, due to their limited processing speed. This demo offloads the majority of the processing to CIPs (a total of 24 TODO: verify), allowing the 8-bit MCU to easily handle the leftover processing.

This README covers a brief usage guide, and other surface level info about the demo. The cold plate was made so different aspect/functionality of the microcontroller could be copied/adapted to various applications, not with the intention someone would build their own cold plate. Because of this, there is no how-to guide to build up the hardware. However, all PCB, CAD files, and non-standard BOM components are included in the repo for reference.

<!--ADD IN LATER AFTER APP NOTE IS PUBLISHED: For in-depth information on the implementation details of this demo, check out the app note listed in the related documentation. -->

## Related Documentation
- [PIC16F17146 Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/-PIC16F17126-46-Full-Featured-Microcontrollers-Data-Sheet-40002343C.pdf)
- [EA OLEDM204 datasheet](https://www.lcd-module.de/fileadmin/html-seiten/eng/pdf/doma/oledm204-ae.pdf)

TODO: get these
- Peltier Element - get ID
- NTC thermistor curves?

## Software Used

- [MPLAB® X IDE 6.0.0](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide) or newer
- [MPLAB XC8 2.36.0](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers) or newer compiler
- [MPLAB Code Configurator](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator) (MCC) 5.1.9 or newer
- [MPLAB Mindi&trade; Analog Simulator](https://www.microchip.com/en-us/tools-resources/develop/analog-development-tool-ecosystem/mplab-mindi-analog-simulator)

## Hardware Used

- [PIC16F17146](https://www.microchip.com/en-us/product/PIC16F17146) DIP
- [Curiosity Development Board](https://www.microchip.com/en-us/development-tool/dm164137) (used during development only)

## Major Functions

<!-- TODO after app note is published: In depth information on each major function system can be found in the App Note in related documentation. -->
These are the major functions are implemented nearly 100% in CIPs, leaving the CPU to be available to monitor and set various feedback and control signals at a high level instead of having to manually manipulate every signal out of the MCU.

**Current control and monitoring** – OPA1, DAC1, DAC2, CMP1, and ADCC CIPs create a CPU-independent system for controlling/monitoring the current being pulled by the Peltier plate. DAC2/CMP2 are used to detect current flowing. The amplified current sense output of the OP-AMP is compared to a small reference voltage (from DAC2) using CMP2. If it is greater, CMP2 is triggered, indiciating current is flowing through the system. DAC1/CMP1 work in the same way, but are used to limit the top-end current limit. If the DAC1 value is exceeded by the OP-AMP output, the current control signal is cutoff to keep current within set parameters.

**Cold plate, heatsink, and MCU temperature monitoring** – The microcontroller monitors the temperature at these 3 different locations by reading thermistors for the plate, heatsink, and an internal temperature module for the MCU. The analog values of each are read by the ADCC CIP (which is configured to use the FVR CIP as it's Vref).

**Functional safety supported persistent storage & functional monitoring** –  Using the NVM & CRC CIPs, user settings are saved to EEPROM along with a checksum. On startup, the checksum is re-validated to ensure data integrity. These CIPs reduce code size & free the CPU from having to perform these tasks, offloading it to dedicated hardware. Also, since the cold plate involves high currents and potentially hazardous temperatures, a WWDT CIP ensures the CPU is always available to handle the safety critical tasks. The MCU is automatically reset if some code is stalling the CPU, ensuring safety is not compromised.

**Single speed fan control with dual fan speed monitoring** – A PWM CIP generates a speed control signal for system fans. This allows the fans to remain quiet until the heatsink gets hot. 2 Timer CIPs also monitor the individual RPMs of channel 1 and 2 fans, providing feedback to display on the UI.

**User interface** – The user interacts with the cold plate through a pushbutton rotary encoder and an OLED display. The rotary encoder feeds into 2 CLC CIPs to filter the signal, then into 2 timer CIPs that act as counters. This means the CPU doesn't need to track rotary encoder movements. The OLED is controlled with the on-chip MSSP1 module using specifically I2C. Since there is dedicated MSSP hardware, the CPU doesn’t need to manually send all the data either. Lastly, the rotary encoder has 2 LED build in - an orange and blue LED. Using a PWM CIP, this gives visual indication of the cold plate's status:

| Color | Cold plate status |
| --- | --- |
| Breathing Purple | Standby |
| Breathing Blue | Actively Cooling |
| Sold Blue | At Target Temperature |
| Solid Orange | Error |

**Misc CIPs** - UART1 prints messages for debugging. Timer0 creates periodic callbacks so code can run every 1ms, 100ms, 1s, etc.

## Operation

On boot, a standby screen shows the current plate temperature, the set temperature, and whether the product is in demo mode (which limits the lowest temperature for safety)

![Main Menu](images/main_menu.jpg)

Pressing the rotary encoder button brings up a menu that can be used to change various running parameters:

| Name | Function |
| --- | --- |
| Go Back | Return to Standby screen |
| Start | Turn on plate, go to running status screen |
| Set Temperature | Change temp to cool to |
| Hysteresis | Sets degrees above/below target temp plate can be|
| Change Units | Select Celsius or Fahrenheit|
| Show Icons | Display text or icons in running status screen |
| About | Lists developer and version info |
| Demo Mode Toggle | Password protected way to disable demo mode|

![Top Menu](images/top_menu.jpg)
![Bottom Menu](images/bottom_menu.jpg)

Upon pressing `Start`, the MCU begins checking for various errors, and if all checks pass, the plate power is enabled and the user is brought to a running status screen which shows the plate target temp, current temp, heatsink temp, MCU temp, current being drawn, and heatsink fan RPM.

![Running Menu](images/running.jpg)

If any of the error checks fail at any time, power to the plate is cut, and a troubleshooting error message displays on the screen. Press the rotary encoder to clear the error and return to the standy screen. If the error is not remedied and the plate is started again, it will loop back to the same error screen.

![Error Menu](images/error.jpg)

Below is a list of the various possible errors that are continuously checked for during running operation:

| Name | Cause |
| --- | --- |
| PELTIER_FAN1_ERROR | The heatsink fan is unplugged |
| PELTIER_OVERCURRENT_ERROR | More current is pulled than software allows (10A)|
| PELTIER_POWER_ERROR | No power is detected when the plate should be pulling current |
| PELTIER_INT_OVERHEAT | Internal MCU temperature is too hot (70C)|
| PELTIER_HEATSINK_OVERHEAT | Heatsink is too hot (80C)|
| PELTIER_SENSE_HOT_OPEN | Thermocouple for heatsink is disconnected |
| PELTIER_SENSE_COLD_OPEN | Thermocouple for plate temp is disconnected |
| PELTIER_PLATE_TEMP_LIMIT | Cold plate is below safe temperature |

Once started, pressing the rotary encoder button and selecting `Cancel` stops the plate and returns to the standby menu

## Summary
This README covered a brief overview of the functionality of The Cold Plate as well as cover a usage overview. 

<!-- TODO: Add after app note is published: More in-depth information can be found in the app note listed in [Related Documentation](#related-documentation). -->
