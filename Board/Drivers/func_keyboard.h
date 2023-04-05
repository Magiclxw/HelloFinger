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

typedef enum{
	button_NULL = 0,
	button_LEFT = 1,
	button_RIGHT= 2,
	button_MID  = 4
}BUTTON_VALUE;

void ABS_Keyboard_Wheel_Ctrl(uint8_t step);
void ABD_Keyboard_Move_Ctrl(uint8_t* pos_x,uint8_t* pos_y);
void ABS_Keyboard_Button_Ctrl(BUTTON_VALUE button);
void REL_Keyboard_Wheel_Ctrl(uint8_t step);
void REL_Keyboard_Move_Ctrl(uint8_t dir_x,uint8_t dir_y);
void REL_Keyboard_Button_Ctrl(BUTTON_VALUE button);

void UnLock(uint16_t X,uint16_t Y);

#endif