/**
 * CLC4 Generated Driver File
 * 
 * @file clc4.c
 * 
 * @ingroup  clc4
 * 
 * @brief This is the generated driver implementation file for the CLC4 driver.
 *
 * @version CLC4 Driver Version 1.0.1
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


#include <xc.h>
#include "../clc4.h"


void CLC4_Initialize(void)
{
    
    // SLCT 0x3; 
    CLCSELECT = 0x3;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0xD;
    // LCD1S CWG1A_OUT; 
    CLCnSEL0 = 0x2D;
    // LCD2S C2_OUT; 
    CLCnSEL1 = 0x20;
    // LCD3S PWM1_OUT1; 
    CLCnSEL2 = 0x16;
    // LCD4S TMR0; 
    CLCnSEL3 = 0xE;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x0;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x0;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N enabled; LCG4D1T disabled; LCG4D2N enabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x5;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 1-input transparent latch with S and R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x87;

}


bool CLC4_OutputStatusGet(void)
{
    return(CLCDATAbits.CLC4OUT);
}
/**
 End of File
*/
