#ifndef RUNNINGMENUS_H
#define	RUNNINGMENUS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "OLED.h"
#include "fanControl.h"
#include "tempMonitor.h"
#include "settingMenus.h"
    
void runningMenus_runningSetup(void);
void runningMenus_runningUpdate(int16_t moves);

void runningMenus_errorSetup(void);
void runningMenus_errorUpdate(int16_t moves);


#ifdef	__cplusplus
}
#endif

#endif	/* RUNNINGMENUS_H */

