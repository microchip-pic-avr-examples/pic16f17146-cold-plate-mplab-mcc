#include "OLED.h"
#include "settings.h"

#define OLED_CONTROLLER_ADDR 0x3C // 7-bit client address

// SSD1311 expects a command byte that specifies the following byte as
// a command or data, so every interaction is at least 2 bytes

void OLED_command(uint8_t cmd_byte){
    uint8_t send_data[2];
    send_data[0] = 0x80;
    send_data[1] = cmd_byte;
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, send_data, 2);
}

void OLED_data(uint8_t cmd_byte){
    uint8_t send_data[2];
    send_data[0] = 0xC0;
    send_data[1] = cmd_byte;
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, send_data, 2);
}

void OLED_init(void){
    // flash reset signal
    IO_RB4_SetHigh();
    __delay_ms(10);
    IO_RB4_SetLow();
    __delay_ms(10);
    IO_RB4_SetHigh();
    
    //OLED init command sequence
    // Breakdown of each command is below this compressed version
    uint8_t init_data[80] = {
        // Turn on sequence
        0x80, 0x08,
        0x80, 0x3A,
        0x80, 0x72,
        0x80, 0x09,
        0x80, 0x05,
        0x80, 0x38,
        0x80, 0x3A,
        0x80, 0x72,
        0xC0, 0x00,
        0x80, 0x38,
        // Degree symbol custom character
        0x80, 0x40,
        0xC0, 0x07,
        0x80, 0x41,
        0xC0, 0x05,
        0x80, 0x42,
        0xC0, 0x07,
        0x80, 0x43,
        0xC0, 0x00,
        0x80, 0x44,
        0xC0, 0x00,
        0x80, 0x45,
        0xC0, 0x00,
        0x80, 0x46,
        0xC0, 0x00,
        0x80, 0x47,
        0xC0, 0x00,
        // MCU Custom character, left half
        0x80, 0x48,
        0xC0, 0x0F,
        0x80, 0x49,
        0xC0, 0x18,
        0x80, 0x4A,
        0xC0, 0x08,
        0x80, 0x4B,
        0xC0, 0x18,
        0x80, 0x4C,
        0xC0, 0x08,
        0x80, 0x4D,
        0xC0, 0x18,
        0x80, 0x4E,
        0xC0, 0x0F
    };
    uint8_t init_data2[80] = {
        0x80, 0x4F,
        0xC0, 0x00,
        // MCU Custom character, right half
        0x80, 0x50,
        0xC0, 0x3C,
        0x80, 0x51,
        0xC0, 0x06,
        0x80, 0x52,
        0xC0, 0x04,
        0x80, 0x53,
        0xC0, 0x06,
        0x80, 0x54,
        0xC0, 0x04,
        0x80, 0x55,
        0xC0, 0x06,
        0x80, 0x56,
        0xC0, 0x3C,
        0x80, 0x57,
        0xC0, 0x00,
        // Heatsink custom character, left half
        0x80, 0x58,
        0xC0, 0x1F,
        0x80, 0x59,
        0xC0, 0x12,
        0x80, 0x5A,
        0xC0, 0x12,
        0x80, 0x5B,
        0xC0, 0x12,
        0x80, 0x5C,
        0xC0, 0x12,
        0x80, 0x5D,
        0xC0, 0x10,
        0x80, 0x5E,
        0xC0, 0x10,
        0x80, 0x5F,
        0xC0, 0x00,
        // Heatsink custom character, right half
        0x80, 0x60,
        0xC0, 0x1F,
        0x80, 0x61,
        0xC0, 0x09,
        0x80, 0x62,
        0xC0, 0x09
    };
    uint8_t init_data3[80] = {
        0x80, 0x63,
        0xC0, 0x09,
        0x80, 0x64,
        0xC0, 0x09,
        0x80, 0x65,
        0xC0, 0x01,
        0x80, 0x66,
        0xC0, 0x01,
        0x80, 0x67,
        0xC0, 0x00,
        // Plate custom character, left half
        0x80, 0x68,
        0xC0, 0x04,
        0x80, 0x69,
        0xC0, 0x04,
        0x80, 0x6A,
        0xC0, 0x04,
        0x80, 0x6B,
        0xC0, 0x04,
        0x80, 0x6C,
        0xC0, 0x04,
        0x80, 0x6D,
        0xC0, 0x03,
        0x80, 0x6E,
        0xC0, 0x1F,
        0x80, 0x6F,
        0xC0, 0x00,
        // Plate custom character, right half
        0x80, 0x70,
        0xC0, 0x04,
        0x80, 0x71,
        0xC0, 0x06,
        0x80, 0x72,
        0xC0, 0x05,
        0x80, 0x73,
        0xC0, 0x06,
        0x80, 0x74,
        0xC0, 0x04,
        0x80, 0x75,
        0xC0, 0x18,
        0x80, 0x76,
        0xC0, 0x1F
    };
    uint8_t init_data4[8] = {
        0x80, 0x77,
        0xC0, 0x00,
        // Turn on display
        0x80, 0x0C,
        0x80, 0x01
    };
    
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, init_data, 80);
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, init_data2, 80);
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, init_data3, 80);
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, init_data4, 8);
    
    
// issue OLED init command sequence
// leave these here in case the init sequence needs modded in the future
//    OLED_command(0x08); // turn off display
//    OLED_command(0x3A); // FunctionSet: N=1 BE=0 RE=1 IS=0
//    OLED_command(0x72); // ROM Selection (RE muss 1 sein)
//    OLED_command(0x09); // 3/4-line mode
//    OLED_command(0x05); // View 0°
//    OLED_command(0x38); // FunctionSet: N=1 DH=0 RE=0 IS=0 (4-line))
//    // set RE to 1
//    OLED_command(0x3A); // FunctionSet: N=1 BE=0 RE=1 IS=0
//    // select ROM A
//    OLED_command(0x72); // ROM Selection (RE muss 1 sein)
//    OLED_data(0x00); // ROM_A = 0x00, ROM_B = 0x04, ROM_C = 0x0C
//    // set RE back to 0
//    OLED_command(0x38); // FunctionSet: N=1 DH=0 RE=0 IS=0
//
//    // Degree symbol custom character
//    OLED_command(0b01000000); // set CGRAM address to row 0
//    OLED_data(0b00000111); // insert first row of data
//    OLED_command(0b01000001); // set CGRAM address to row 1
//    OLED_data(0b00000101); // insert second row of data
//    OLED_command(0b01000010); // CGRAM address to row 2
//    OLED_data(0b00000111);
//    OLED_command(0b01000011);
//    OLED_data(0b00000000);
//    OLED_command(0b01000100);
//    OLED_data(0b00000000);
//    OLED_command(0b01000101);
//    OLED_data(0b00000000);
//    OLED_command(0b01000110);
//    OLED_data(0b00000000);
//    OLED_command(0b01000111);
//    OLED_data(0b00000000);
//    
//    // MCU custom character
//    // Takes up 2 data slots
//    // Left half first
//    OLED_command(0b01001000); // set CGRAM address to row 8
//    OLED_data(0b00001111); // insert first row of data
//    OLED_command(0b01001001); // set CGRAM address to row 9
//    OLED_data(0b00011000);
//    OLED_command(0b01001010);
//    OLED_data(0b00001000);
//    OLED_command(0b01001011);
//    OLED_data(0b00011000);
//    OLED_command(0b01001100);
//    OLED_data(0b00001000);
//    OLED_command(0b01001101);
//    OLED_data(0b00011000);
//    OLED_command(0b01001110);
//    OLED_data(0b00001111);
//    OLED_command(0b01001111);
//    OLED_data(0b00000000);
//    // Right half of MCU custom character    
//    OLED_command(0b01010000); // set CGRAM address to row 16
//    OLED_data(0b00111100); // insert first row of data
//    OLED_command(0b01010001); // set CGRAM address to row 17
//    OLED_data(0b00000110);
//    OLED_command(0b01010010);
//    OLED_data(0b00000100);
//    OLED_command(0b01010011); 
//    OLED_data(0b00000110);
//    OLED_command(0b01010100);
//    OLED_data(0b00000100);
//    OLED_command(0b01010101);
//    OLED_data(0b00000110);
//    OLED_command(0b01010110);
//    OLED_data(0b00111100);
//    OLED_command(0b01010111);
//    OLED_data(0b00000000);
//    
//    // Heatsink custom char left half
//    OLED_command(0b01011000); // set CGRAM address to row 24
//    OLED_data(0b00010000); // insert first row of data
//    OLED_command(0b01011001); // set CGRAM address to row 15
//    OLED_data(0b00010000);
//    OLED_command(0b01011010);
//    OLED_data(0b00010010);
//    OLED_command(0b01011011); 
//    OLED_data(0b00010010);
//    OLED_command(0b01011100);
//    OLED_data(0b00010010);
//    OLED_command(0b01011101);
//    OLED_data(0b00010010);
//    OLED_command(0b01011110);
//    OLED_data(0b00011111);
//    OLED_command(0b01011111);
//    OLED_data(0b00000000);
//    
//    // Right half
//    OLED_command(0b01100000); // set CGRAM address to row 24
//    OLED_data(0b00000001); // insert first row of data
//    OLED_command(0b01100001); // set CGRAM address to row 15
//    OLED_data(0b00000001);
//    OLED_command(0b01100010);
//    OLED_data(0b00001001);
//    OLED_command(0b01100011); 
//    OLED_data(0b00001001);
//    OLED_command(0b01100100);
//    OLED_data(0b00001001);
//    OLED_command(0b01100101);
//    OLED_data(0b00001001);
//    OLED_command(0b01100110);
//    OLED_data(0b00011111);
//    OLED_command(0b01100111);
//    OLED_data(0b00000000);
//    
//    // Plate custom char left half
//    OLED_command(0b01101000); // set CGRAM address to row 24
//    OLED_data(0b00000100); // insert first row of data
//    OLED_command(0b01101001); // set CGRAM address to row 15
//    OLED_data(0b00000100);
//    OLED_command(0b01101010);
//    OLED_data(0b00000100);
//    OLED_command(0b01101011); 
//    OLED_data(0b00000100);
//    OLED_command(0b01101100);
//    OLED_data(0b00000100);
//    OLED_command(0b01101101);
//    OLED_data(0b00000011);
//    OLED_command(0b01101110);
//    OLED_data(0b00011111);
//    OLED_command(0b01101111);
//    OLED_data(0b00000000);
//    
//    // Plate custom char right half
//    OLED_command(0b01110000); // set CGRAM address to row 24
//    OLED_data(0b00000100); // insert first row of data
//    OLED_command(0b01110001); // set CGRAM address to row 15
//    OLED_data(0b00000110);
//    OLED_command(0b01110010);
//    OLED_data(0b00000101);
//    OLED_command(0b01110011); 
//    OLED_data(0b00000110);
//    OLED_command(0b01110100);
//    OLED_data(0b00000100);
//    OLED_command(0b01110101);
//    OLED_data(0b00011000);
//    OLED_command(0b01110110);
//    OLED_data(0b00011111);
//    OLED_command(0b01110111);
//    OLED_data(0b00000000);
//    
//    OLED_command(0x0C); // disable cursor & blinking during display on
//    OLED_command(0x01); // Clear display
}

void OLED_clear(void){
    OLED_command(0x01); // Clear display
    OLED_command(0x0C); // disable cursor & blinking during display on
}

void OLED_clear_line(void){
    OLED_writeSpaces(20);
}

void OLED_writeString(char *string){
    for(int i = 0; i < strlen(string); i++){
        OLED_data((uint8_t)string[i]);
    }
}

void OLED_writeTempUnit(void){
    OLED_data(0b00000000);
    (settings_getSetting(SETTINGS_TEMP_UNIT) == 'C') ? OLED_writeString("C") : OLED_writeString("F");
}

void OLED_writeSpaces(uint8_t spaces){
    char disp_buff[21];
    int i = 0;
    while(i < spaces && i < 20){
        disp_buff[i] = ' ';
        i++;
    }
    disp_buff[i] = '\0';
    OLED_writeString(disp_buff);
}