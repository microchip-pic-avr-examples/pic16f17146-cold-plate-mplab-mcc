#ifndef NAVMENU_H
#define	NAVMENU_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "OLED.h"
#include "UI.h"

typedef struct {
    char **options;
    size_t size;
    uint8_t top_item; // keeps track of menu item positions
    uint8_t ast_pos; // selection is on line 1-4
} menu_t;

void navMenu_setup(void);
void navMenu_populate(uint8_t offset, uint8_t asterisk_pos);
void navMenu_update(int16_t moves);
void navMenu_scroll(int16_t moves);
void navMenu_updateAsterisk(uint8_t old_pos, uint8_t new_pos);
void navMenu_updateArrows(void);
UI_STATE navMenu_getSelected(void);

#ifdef	__cplusplus
}
#endif

#endif	/* NAVMENU_H */

