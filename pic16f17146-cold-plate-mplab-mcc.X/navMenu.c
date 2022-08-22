#include "navMenu.h"

// MENU OLED FUNTIONS
const char* options[] = {"Go Back", "Start", "Set Temperature", "Change Units", "Limit Current", "About", "Demo Mode Toggle"};

menu_t menu = {
.options = options,
.size = (sizeof(options) / sizeof(options[0])),
.top_item = 0, // menu item currently on line 1
.ast_pos = 0 // asterisk line (1-4))
};

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
        OLED_writeString(" ");
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
                navMenu_updateAsterisk(menu.ast_pos, menu.ast_pos+moves);
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
                navMenu_updateAsterisk(menu.ast_pos, menu.ast_pos+moves);
                menu.ast_pos+=moves;
                moves = 0;
            }
        }
        navMenu_scroll(moves);
    }
//            // scroll menu
//            if((menu.ast_pos == 0 && moves < 0) || (menu.ast_pos == OLED_LINE_NUM-1 && moves > 0)){ // if asterisk at top or bottom of page
//                    navMenu_scroll(moves); // scroll menu
//
//            } else { // move asterisk & check if scrolling needs to occur
//                if(moves < 0)
//
//            }
}

void navMenu_scroll(int16_t moves){
    int8_t scroll_room = 0;
    if(moves > 0){ // scroll down
        scroll_room = menu.size - (menu.top_item+OLED_LINE_NUM);
        if(scroll_room){ // if there is room to scroll down
            moves = (moves < scroll_room) ? moves : scroll_room; // don't scroll down more than there is room
            menu.top_item+=moves;
            navMenu_populate(menu.top_item, OLED_LINE_NUM-1);
        }
    } else if(moves < 0){ // scroll up
        scroll_room = -menu.top_item;
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
    OLED_writeString(" "); // replace with space}
    
    // place new asterisk
    OLED_command(line_address[new_pos]);
    OLED_writeString("*");
}    
    
    
void navMenu_updateArrows(void){
    OLED_command(line_address[0]+19);
    if(menu.top_item != 0){ // show top arrow
        OLED_data(0b11011110); // up arrow code
    } else {
        OLED_writeString(" ");
    }

    OLED_command(line_address[3]+19); //show bottom arrow   
    if((menu.top_item + OLED_LINE_NUM) < menu.size){
        OLED_data(0b11100000); // down arrow code
    } else{
        OLED_writeString(" ");
    }
}

UI_STATE navMenu_getSelected(void){
    int8_t selected = menu.top_item + menu.ast_pos;
    
    if(!strcmp(options[selected], "Go Back")){
        return STANDBY; // TODO: change this depending on what settings have been changed
    } else if(!strcmp(options[selected], "Start")){
        return START;
    } else if(!strcmp(options[selected], "Set Temperature")){
        return SET_TEMPERATURE;
    } else if(!strcmp(options[selected], "Change Units")){
        return CHANGE_UNITS;
    } else if(!strcmp(options[selected], "Limit Current")){
        return LIMIT_CURRENT;
    } else if(!strcmp(options[selected], "About")){
        return ABOUT;
    } else if(!strcmp(options[selected], "Demo Mode Toggle")){
        return DEMO_MODE_TOGGLE;
    }
    return ERROR;
}