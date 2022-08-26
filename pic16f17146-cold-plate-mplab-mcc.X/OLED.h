#ifndef OLED_H
#define	OLED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include <string.h>
#include "mssp1_host.h"

#define OLED_LINE_NUM 4
// address to put the OLED cursor at the start of each line
uint8_t line_address[4] = {0x80, 0xA0, 0xC0, 0xE0};
    
void OLED_command(uint8_t cmd_byte);
void OLED_data(uint8_t cmd_byte);
void OLED_init(void);
void OLED_writeString(char *string);
void OLED_clear(void);
void OLED_clear_line(void);
void OLED_writeTempUnit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* OLED_H */
