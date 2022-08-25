/**
 * CONFIGURATION BITS Generated Driver Source File
 * 
 * @file config_bits.c
 * 
 * @ingroup config_bitsdriver
 * 
 * @brief This is the generated Device Configuration Bits file.
 *
 * @version Driver Version 2.0.1
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// Configuration bits: selected in the GUI
//CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_32MHz    // Reset Oscillator Selection bits->HFINTOSC (32 MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config VDDAR = HI    // VDD Range Analog Calibration Selection bit->Internal analog systems are calibrated for operation between VDD = 2.3 - 5.5V
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

//CONFIG2
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR
#pragma config PWRTS = PWRT_64    // Power-up Timer Selection bits->PWRT set at 64 ms
#pragma config LPBOREN = OFF    // Low-Power BOR Enable bit->ULPBOR disabled
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset enabled, SBOREN bit is ignored
#pragma config DACAUTOEN = ON    // DAC Buffer Automatic Range Select Enable bit->DAC Buffer reference range is automatically determined by module hardware
#pragma config BORV = LO    // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config ZCD = OFF    // ZCD Disable bit->ZCD module is disabled; ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY = OFF    // PPSLOCKED One-Way Set Enable bit->The PPSLOCKED bit can be set and cleared as needed (unlocking sequence is required)
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

//CONFIG3
#pragma config WDTCPS = WDTCPS_11    // WDT Period Select bits->Divider ratio 1:65536
#pragma config WDTE = SWDTEN    // WDT Operating Mode bits->WDT enabled/disabled by SEN bit
#pragma config WDTCWS = WDTCWS_6    // WDT Window Select bits->window always open (100%); no software control; keyed access required
#pragma config WDTCCS = LFINTOSC    // WDT Input Clock Select bits->WDT reference clock is the 31.0 kHz LFINTOSC

//CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF    // Storage Area Flash (SAF) Enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block is NOT write protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block is NOT write protected
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration Register is NOT write protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM is NOT write protected
#pragma config WRTSAF = OFF    // Storage Area Flash (SAF) Write Protection bit->SAF is NOT write protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored

//CONFIG5
#pragma config CP = OFF    // Program Flash Memory Code Protection bit->Program Flash Memory code protection is disabled
#pragma config CPD = OFF    // Data EEPROM Code Protection bit->Data EEPROM code protection is disabled

/**
 End of File
*/