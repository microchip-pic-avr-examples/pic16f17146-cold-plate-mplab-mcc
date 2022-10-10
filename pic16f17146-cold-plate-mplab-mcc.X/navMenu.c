#include "navMenu.h"

// MENU OLED FUNTIONS
char* options[] = {"Go Back", "Start", "Set Temperature", "Change Units", "Show Icons", "Hysteresis", "About", "Demo Mode Toggle"};

menu_t menu = {
.options = options,
.size = (sizeof(options) / sizeof(options[0])),
.top_item = 0, // menu item currently on line 1
.ast_pos = 0 // asterisk line (1-4))
};

void navMenu_changeStartOptions(bool start){
    if(start){
        options[1] = "Start";
        //strcpy(options[1], "Start");
    } else {
        options[1] = "Cancel";
        //strcpy(options[1], "Cancel");
    }
    navMenu_reset();
}

void navMenu_reset(void){
    menu.top_item = 0;
    menu.ast_pos = 0;
}

void navMenu_setup(void){
    navMenu_populate(menu.top_item, menu.ast_pos);
}

void navMenu_populate(uint8_t offset, uint8_t ast_pos){

    // sanity check offset + asterisk_pos
    offset = (offset > OLED_LINE_NUM) ? OLED_LINE_NUM : offset;
    ast_pos = (ast_pos > OLED_LINE_NUM) ? OLED_LINE_NUM : ast_pos;
    
    OLED_clear();
    
    // populate menu options
    for(int i = 0; i < OLED_LINE_NUM; i++){
        OLED_command(line_address[i]);
        OLED_writeSpaces(1);
        OLED_writeString(menu.options[i+offset]);
    }
    
    // place asterisk
    navMenu_updateAsterisk(ast_pos, ast_pos);
    
    // place arrow
    navMenu_updateArrows();
    
}


void navMenu_update(int16_t moves){
    int8_t move_amt = 0;
    int8_t scroll_amt = 0;
    if(moves > 0){ // scroll down
        if(!(menu.ast_pos == OLED_LINE_NUM-1)){ // asterisk is not at bottom of page
            if(moves > OLED_LINE_NUM-1-menu.ast_pos){ // if the move will scroll past the page
                navMenu_updateAsterisk(menu.ast_pos, OLED_LINE_NUM-1); // move to bottom of page
                moves-=(OLED_LINE_NUM-1-menu.ast_pos); // remove number of moves made from moves
                menu.ast_pos=OLED_LINE_NUM-1; // update ast pos
            } else { // otherwise just move asterisk down page
                navMenu_updateAsterisk(menu.ast_pos, (uint8_t)(menu.ast_pos + moves));
                menu.ast_pos+=moves;
                moves = 0;
            }
        }
        navMenu_scroll(moves);
    } else if(moves < 0){ // scroll up
        if(!(menu.ast_pos == 0)){ // asterisk is not at top of page
            if(moves+menu.ast_pos < 0){ // if the move will scroll past the top of the page
                navMenu_updateAsterisk(menu.ast_pos, 0); // move to the top of the page
                moves+=menu.ast_pos; // remove number of moves made from moves
                menu.ast_pos = 0; // update ast_pos
            } else { // otherwise just move asterisk up page
                navMenu_updateAsterisk(menu.ast_pos, (uint8_t)(menu.ast_pos + moves));
                menu.ast_pos+=moves;
                moves = 0;
            }
        }
        navMenu_scroll(moves);
    }
}

void navMenu_scroll(int16_t moves){
    int8_t scroll_room = 0;
    if(moves > 0){ // scroll down
        scroll_room = (int8_t)menu.size - (menu.top_item+OLED_LINE_NUM);
        if(scroll_room){ // if there is room to scroll down
            moves = (moves < scroll_room) ? moves : scroll_room; // don't scroll down more than there is room
            menu.top_item+=moves;
            navMenu_populate(menu.top_item, OLED_LINE_NUM-1);
        }
    } else if(moves < 0){ // scroll up
        scroll_room = (int8_t)-menu.top_item;
        if(scroll_room){
            moves = (moves > scroll_room ? moves : scroll_room); // make sure we don't scroll move than there is room
            menu.top_item+=moves;
            navMenu_populate(menu.top_item, 0);
        }
    }
}

void navMenu_updateAsterisk(uint8_t old_pos, uint8_t new_pos){
    // remove old asterisk
    OLED_command(line_address[old_pos]); // put cursor on asterisk
    OLED_writeSpaces(1);
    
    // place new asterisk
    OLED_command(line_address[new_pos]);
    OLED_writeString("*");
}    
    
    
void navMenu_updateArrows(void){
    OLED_command(line_address[0]+19);
    if(menu.top_item != 0){ // show top arrow
        OLED_data(0b11011110); // up arrow code
    } else {
        OLED_writeSpaces(1);
    }

    OLED_command(line_address[3]+19); //show bottom arrow   
    if((menu.top_item + OLED_LINE_NUM) < menu.size){
        OLED_data(0b11100000); // down arrow code
    } else{
        OLED_writeSpaces(1);
    }
}

UI_STATE navMenu_getSelected(void){
    int8_t selected = (int8_t)menu.top_item + menu.ast_pos;
    switch(selected){
        case 0:
            if(UI_isRunning()){
                return RUNNING;
            } else {
                return STANDBY;
            }
            break;
        case 1:
            if(UI_isRunning()){
                peltierControl_stop(); // already running
                return STANDBY;
            } else{
                peltierControl_start(); // not running
                return RUNNING;
            }
            break;
        case 2:
            return SET_TEMPERATURE;
            break;
        case 3:
            return CHANGE_UNITS;
            break;
        case 4:
            return SHOW_ICONS;
            break;
        case 5:
            return HYSTERESIS;
            break;
        case 6:
            return ABOUT;
            break;
        case 7:
            return DEMO_MODE_TOGGLE;
            break;
    }
    return ERROR;
}
