#include "func_keyboard.h"
#include "usart.h"
#include "ch9329.h"
#include "delay.h"

uint8_t tests[10]={"asd13579"};
/* ����������ݰ� */
uint8_t Absolute_Mouse[16] = {0x57,0xAB,0x00,0x04,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x0D,0x0A};	//�������

/* ���������ݰ� */
uint8_t	Relative_Mouse[14] = {0x57,0xAB,0x00,0x05,0x05,0x01,0x00,0x00,0x00,0x00,0x00,0xFF,0x0D,0x0A};



/**�����ַ����ָ��*/
void Sendtest(uint8_t *asc)
{
	uint16_t len = toASCLL(asc);
	for(int i=0;i<len;i++){
		SendCommand((uint8_t*)ascll[result[i]]);	//����ascll�ַ������е�result[i]���ַ�
	}
}

/**
* @brief	����������ݰ�
* @param	step:���ֻ�������
* @param	pos_x:x�����ƶ�·��
* @param	pos_y:y�����ƶ�·��
* @param	button:���°���	0x01:�����0x02:�Ҽ���0x04:�м�
* @date	2023-4-15 20:13:27
* @return 
*/
void ABD_Mouse_Ctrl(uint8_t step,uint8_t* pos_x,uint8_t* pos_y,BUTTON_VALUE button)
{
	Absolute_Mouse[ABSOLUTE_MOUSE_WHEEL] = step;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X] = pos_x[0];
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X+1] = pos_x[1];
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y] = pos_y[0];
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y+1] = pos_y[1];
	Absolute_Mouse[ABSOLUTE_MOUSE_BTN] = button;
	
	CH9329_Generate_Checksum(Absolute_Mouse,12);
	
	HAL_UART_Transmit(&KEYOUT,Absolute_Mouse,16,1000);
	
	Absolute_Mouse[ABSOLUTE_MOUSE_WHEEL] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_X+1] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_DIR_Y+1] = 0;
	Absolute_Mouse[ABSOLUTE_MOUSE_BTN] = 0;
}

/**
* @brief	���������ݰ�
* @param	step:���ֻ�������
* @param	pos_x:x�����ƶ�·��
* @param	pos_y:y�����ƶ�·��
* @param	button:���°���	0x01:�����0x02:�Ҽ���0x04:�м�
* @date	2023-4-15 20:36:24
* @return 
*/
void REL_Mouse_Ctrl(uint8_t step,uint8_t dir_x,uint8_t dir_y,BUTTON_VALUE button)
{
	Relative_Mouse[RELATIVE_MOUSE_WHEEL] = step;
	Relative_Mouse[RELATIVE_MOUSE_DIR_X] = dir_x;
	Relative_Mouse[RELATIVE_MOUSE_DIR_Y] = dir_y;
	Relative_Mouse[RELATIVE_MOUSE_BTN] = button;
	CH9329_Generate_Checksum(Relative_Mouse,10);
	HAL_UART_Transmit(&KEYOUT,Relative_Mouse,14,1000);
	Relative_Mouse[RELATIVE_MOUSE_WHEEL] = 0;
	Relative_Mouse[RELATIVE_MOUSE_DIR_X] = 0;
	Relative_Mouse[RELATIVE_MOUSE_DIR_Y] = 0;
	Relative_Mouse[RELATIVE_MOUSE_BTN] = 0;
}

/**
* @brief	��������
* @param	��X��Y��1920*1080:  X=960,Y=625
* @date	2023-4-15 20:38:20
* @return 
*/
void UnLock(uint16_t X,uint16_t Y,uint8_t* password,uint8_t len)
{
	//Cal(X,Y);
	uint8_t pos_x[2] = {X>>8,(uint8_t)X};
	uint8_t pos_y[2] = {Y>>8,(uint8_t)Y};
	
	ABD_Mouse_Ctrl(0,pos_x,pos_y,button_NULL);
	ABD_Mouse_Ctrl(0,0,0,button_LEFT);
	ABD_Mouse_Ctrl(0,0,0,button_NULL);
	
	Sendtest(password);
	
	SendCommand(LeftEnter);
}
















