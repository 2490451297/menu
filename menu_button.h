#ifndef __MENU_BUTTON_H
#define __MENU_BUTTON_H

#include "headfile.h"

#define UP_BUTTON C31
#define DOWN_BUTTON C27
#define SURE_BUTTON C26
#define CANCEL_BUTTON C4

#define BUTTON_UP_EVENT 1
#define BUTTON_DOWN_EVENT 2
#define BUTTON_SURE_EVENT 3
#define BUTTON_CANCEL_EVENT 4

extern void menuButtonInit(void);
extern void menuButtonIRQInit(void);
extern uint8 menuPressEvent(void);

#endif