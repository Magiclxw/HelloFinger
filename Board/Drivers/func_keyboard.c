#include "func_keyboard.h"
#include "usart.h"
#include "ch9329.h"

uint8_t tests[10]={"asd13579"};
/* 绝对鼠标数据包 */
uint8_t Absolute_Mouse[16] = {0x57,0xAB,0x00,0x04,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x0D,0x0A};	//按下左键

/* 相对鼠标数据包 */
uint8_t	Relative_Mouse[14] = {0x57,0xAB,0x00,0x05,0x05,0x01,0x00,0x00,0x00,0x00,0x00,0xFF,0x0D,0x0A};



/**发送字符输出指令*/
void Sendtest(uint8_t *asc)
{
	uint16_t len = toASCLL(asc);
	for(int i=0;i<len;i++){
		SendCommand((uint8_t*)ascll[result[i]]);	//发送ascll字符数组中第result[i]个字符
	}
}

void ABS_Keyboard_Wheel_Ctrl(uint8_t step)
{
	Absolute_Mouse[ABSOLUTE_MOUSE_WHEEL] = step;
	CH9329_Generate_Checksum(Absolute_Mouse,9);
	HAL_UART_Transmit(&KEYOUT,Absolute_Mouse,16,1000);
	Absolute_Mouse[ABSOLUTE_MOUSE_WHEEL] = 0;
}

void ABD_Keyboard_Move_Ctrl(uint8_t* pos_x,uint8_t* pos_y)
{
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X] = pos_x[0];
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X+1] = pos_x[1];
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y] = pos_y[0];
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y+1] = pos_y[1];
	
	CH9329_Generate_Checksum(Absolute_Mouse,9);
	
	HAL_UART_Transmit(&KEYOUT,Absolute_Mouse,16,1000);
	
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X+1] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y+1] = 0;
	
}

void ABS_Keyboard_Button_Ctrl(BUTTON_VALUE button)
{
	Absolute_Mouse[ABSOLUTE_MOUSE_BTN] = button;
	CH9329_Generate_Checksum(Absolute_Mouse,10);
	HAL_UART_Transmit(&KEYOUT,Absolute_Mouse,14,1000);
	Absolute_Mouse[ABSOLUTE_MOUSE_BTN] = button_NULL;
}

void REL_Keyboard_Wheel_Ctrl(uint8_t step)
{
	Relative_Mouse[RELATIVE_MOUSE_WHEEL] = step;
	CH9329_Generate_Checksum(Relative_Mouse,10);
	HAL_UART_Transmit(&KEYOUT,Relative_Mouse,14,1000);
	Relative_Mouse[RELATIVE_MOUSE_WHEEL] = 0;
}

void REL_Keyboard_Move_Ctrl(uint8_t dir_x,uint8_t dir_y)
{
	Relative_Mouse[RELATIVE_MOUSE_DIR_X] = dir_x;
	Relative_Mouse[RELATIVE_MOUSE_DIR_Y] = dir_y;
	CH9329_Generate_Checksum(Relative_Mouse,10);
	HAL_UART_Transmit(&KEYOUT,Relative_Mouse,14,1000);
	Relative_Mouse[RELATIVE_MOUSE_DIR_X] = 0;
	Relative_Mouse[RELATIVE_MOUSE_DIR_Y] = 0;
}

void REL_Keyboard_Button_Ctrl(BUTTON_VALUE button)
{
	Relative_Mouse[RELATIVE_MOUSE_BTN] = button;
	CH9329_Generate_Checksum(Relative_Mouse,10);
	HAL_UART_Transmit(&KEYOUT,Relative_Mouse,14,1000);
	Relative_Mouse[RELATIVE_MOUSE_BTN] = button_NULL;
}

//1920*1080:  X=960,Y=625		解锁
void UnLock(uint16_t X,uint16_t Y)
{
	//Cal(X,Y);
	uint8_t pos_x[2] = {X>>8,(uint8_t)X};
	uint8_t pos_y[2] = {Y>>8,(uint8_t)Y};
	
	ABD_Keyboard_Move_Ctrl(pos_x,pos_y);
	ABS_Keyboard_Button_Ctrl(button_LEFT);
	ABS_Keyboard_Button_Ctrl(button_NULL);
	
	Sendtest(tests);
	SendCommand(LeftEnter);
}



















