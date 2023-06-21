#ifndef __KEYBOARD_H
#define __KEYBOARD_H
#include "stm32f1xx.h"

#define ABSOLUTE_MOUSE_WHEEL	11
#define ABSOLUTE_MOUSE_DIR_X	7
#define ABSOLUTE_MOUSE_DIR_Y	9
#define ABSOLUTE_MOUSE_BTN		6

#define RELATIVE_MOUSE_WHEEL	9
#define RELATIVE_MOUSE_DIR_X	7
#define RELATIVE_MOUSE_DIR_Y	8
#define RELATIVE_MOUSE_BTN		6

#define INFO_NUM_LOCK	0x01
#define INFO_CAPS_LOCK	0x02
#define INFO_SCROLL_LOCK	0x04

typedef enum{
	button_NULL = 0,
	button_LEFT = 1,
	button_RIGHT= 2,
	button_MID  = 4
}BUTTON_VALUE;

void ABD_Mouse_Ctrl(uint8_t step,uint8_t* pos_x,uint8_t* pos_y,BUTTON_VALUE button);
void REL_Mouse_Ctrl(uint8_t step,uint8_t dir_x,uint8_t dir_y,BUTTON_VALUE button);

void UnLock(uint16_t X,uint16_t Y,uint8_t* password,uint8_t len);

#endif
