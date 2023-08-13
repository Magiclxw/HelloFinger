#include "func_info.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "ch9329.h"
#include "at24c64.h"
#include "stdlib.h"
#include "func_keyboard.h"

/**
 * @brief	����ָ�ƺ�����Ӧ�Ĺ���
 * @param	cmdtype �������� 1����������	2������	3���˺�+����	4����ݼ�
 * @param	data ������ָ�� data[0]:ָ�ƺ�
 * @date	2023-6-24 11:40:11
 * @return 
 */
uint8_t Func_Store(CMD_TYPE_t cmdtype,uint8_t *data)
{
	uint8_t index = data[0];	//ָ�ƺ�
	switch(cmdtype){
		case TYPE_Windows_Password:
		{
			uint8_t password_len = data[1];
			uint8_t *password = &data[2];
			Func_Store_Win_Password(index,password,password_len);
			break;
		}
		case TYPE_Password:
		{
			uint8_t password_len = data[1];
			uint8_t *password = &data[2];
			Func_Store_Password(index,password,password_len);
			break;
		}
		case TYPE_Account_Password:
		{
			uint8_t account_len = data[1];
			uint8_t *account = &data[2];
			uint8_t password_len = data[account_len + 2];
			uint8_t *password = &data[account_len + 3];
			
			Func_Store_Account_Password(index,account,account_len,password,password_len);
			break;
		}
		case TYPE_Shortcut:
		{
			uint8_t key_len = data[1];
			uint8_t shortcut = data[2];
			uint8_t *key_value = &data[3];
			Func_Store_Shortcut(index,shortcut,key_value,key_len-1);	//key_len-1��ȥ�����Ƽ���ĳ���
			break;
		}
		default:
			break;
	}
}

void Func_Store_Win_Password(uint8_t index,uint8_t *password,uint8_t len)
{
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index,(uint8_t)TYPE_Windows_Password);
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+1,len);
	AT24C64_Write(FINGER_FUNC_ADDR*index+3,password,len);
}

void Func_Store_Password(uint8_t index,uint8_t *password,uint8_t len)
{
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index,(uint8_t)TYPE_Password);
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+1,len);
	AT24C64_Write(FINGER_FUNC_ADDR*index+3,password,len);
}

void Func_Store_Account_Password(uint8_t index,uint8_t *account,uint8_t account_len,uint8_t *password,uint8_t password_len)
{
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index,(uint8_t)TYPE_Account_Password);	//�洢ָ������
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+1,account_len);	//�洢�˺ų���
	AT24C64_Write(FINGER_FUNC_ADDR*index+3,account,account_len);	//�洢�˺�
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+3+account_len+1,password_len);	//�洢���볤��
	AT24C64_Write(FINGER_FUNC_ADDR*index+3+account_len+2,password,password_len);	//�洢����
}

/**
 * @brief		�����ݼ�
 * @param		index ָ������
 * @param		shortcut ���Ƽ���bit7-��Win bit6-��Alt bit5-��Shift bit4-��Ctrl bit3-��Win bit2-��Alt bit1-��Shift bit0- ��Ctrl
 * @param		key ��ͨ��(ASCII��)
 * @param   keyLen ��ͨ�����������6��
 * @date		2023-6-11 10:35:51
 * @return 	NULL
 */
void Func_Store_Shortcut(uint8_t index,uint8_t shortcut,uint8_t *key,uint8_t keyLen)
{
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index,(uint8_t)TYPE_Shortcut);	//�洢ָ������
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+1,keyLen);	//��ݼ�����
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+3,shortcut);	//�洢���Ƽ�
	AT24C64_Write(FINGER_FUNC_ADDR*index+4,key,keyLen-1);	//�洢��ͨ��	keyLen-1:���Ƽ�֮��İ�������
}

uint8_t Func_Exe(uint8_t index)
{
	uint8_t store_type = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index);
	switch (store_type){
		case TYPE_Windows_Password:
		{
			Func_Exe_Win_Password(index);
			break;
		}
		case TYPE_Password:
		{
			Func_Exe_Password(index);
			break;
		}
		case TYPE_Account_Password:
		{
			Func_Exe_Account_Password(index);
			break;
		}
		case TYPE_Shortcut:
		{
			Func_Exe_Shortcut(index);
			break;
		}
		default:return ERROR_MATCH;;
	}
}

uint8_t Func_Exe_Win_Password(uint8_t index)
{
	uint8_t password_len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+1);
	uint8_t *password = (uint8_t *)malloc(password_len);
	AT24C64_Read(FINGER_FUNC_ADDR*index+3,password,password_len);
	
	UnLock(960,265,password,password_len);
	
	free(password);
	return ERROR_PASS;
}

uint8_t Func_Exe_Password(uint8_t index)
{
	uint8_t password_len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+1);
	uint8_t *password = (uint8_t *)malloc(password_len);
	AT24C64_Read(FINGER_FUNC_ADDR*index+3,password,password_len);
	/* �������� */
	
	
	free(password);
	return ERROR_PASS;
}

uint8_t Func_Exe_Account_Password(uint8_t index)
{
	uint8_t account_len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+1);	//��ȡ�˺ų���
	uint8_t *account = (uint8_t *)malloc(account_len);
	AT24C64_Read(FINGER_FUNC_ADDR*index+3,account,account_len);	//��ȡ�˺�
	uint8_t password_len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+3+account_len);	//��ȡ���볤��
	uint8_t *password = (uint8_t *)malloc(password_len);
	AT24C64_Read(FINGER_FUNC_ADDR*index+3+account_len+2,account,account_len);
	/* �����˺š����� */
	
	
	free(account);
	free(password);
	return ERROR_PASS;
}


uint8_t Func_Exe_Shortcut(uint8_t index)
{
	uint8_t len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+1);	//��ݼ�����=���Ƽ�+��ͨ��
	uint8_t key_contral = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+3);
	uint8_t key_normal[6] = {0};
	AT24C64_Read(FINGER_FUNC_ADDR*index+4,key_normal,len);
	
	uint8_t * comb_value = Combination_Key(key_contral,key_normal);
	
	SendCommand(comb_value);
	
	return ERROR_PASS;
}






























