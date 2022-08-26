#include "OLED.h"

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
       // issue OLED init command sequence
    uint8_t init_data[58] = {
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
        0x80, 0x80,
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
        0x80, 0x0C,
        0x80, 0x01
    };
    
    MSSP_WriteBlock(OLED_CONTROLLER_ADDR, init_data, 58);
    
    
//    // issue OLED init command sequence
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
//    // set degree symbol custom character
//    OLED_command(0b10000000); // set DDRAM address to 0
//    OLED_command(0b01000000); // set CGRAM address to row 0
//    OLED_data(0b00000111); // write first row to 1?
//    OLED_command(0b01000001); // set CGRAM address to row 1
//    OLED_data(0b00000101); // write first row to 1?
//    OLED_command(0b01000010); // set CGRAM address to row 2
//    OLED_data(0b00000111); // write first row to 1?
//    OLED_command(0b01000011); // set CGRAM address to row 3
//    OLED_data(0b00000000); // write first row to 1?
//    OLED_command(0b01000100); // set CGRAM address to row 4
//    OLED_data(0b00000000); // write first row to 1?
//    OLED_command(0b01000101); // set CGRAM address to row 5
//    OLED_data(0b00000000); // write first row to 1?
//    OLED_command(0b01000110); // set CGRAM address to row 6
//    OLED_data(0b00000000); // write first row to 1?
//    OLED_command(0b01000111); // set CGRAM address to row 7
//    OLED_data(0b00000000); // write first row to 1?
//    
//    OLED_command(0x0C); // disable cursor & blinking during display on
//    OLED_command(0x01); // Clear display
}

void OLED_clear(void){
    OLED_command(0x01); // Clear display
    OLED_command(0x0C); // disable cursor & blinking during display on
}

void OLED_clear_line(void){
    OLED_writeString("                    "); // disable cursor & blinking during display on
}

void OLED_writeString(char *string){
    for(int i = 0; i < strlen(string); i++){
        OLED_data((uint8_t)string[i]);
    }
}