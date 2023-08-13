#include "func_info.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "ch9329.h"
#include "at24c64.h"
#include "stdlib.h"
#include "func_keyboard.h"

/**
 * @brief	保存指纹号所对应的功能
 * @param	cmdtype 功能类型 1：开机密码	2：密码	3：账号+密码	4：快捷键
 * @param	data 解析的指令 data[0]:指纹号
 * @date	2023-6-24 11:40:11
 * @return 
 */
uint8_t Func_Store(CMD_TYPE_t cmdtype,uint8_t *data)
{
	uint8_t index = data[0];	//指纹号
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
			Func_Store_Shortcut(index,shortcut,key_value,key_len-1);	//key_len-1：去除控制键后的长度
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
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index,(uint8_t)TYPE_Account_Password);	//存储指令类型
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+1,account_len);	//存储账号长度
	AT24C64_Write(FINGER_FUNC_ADDR*index+3,account,account_len);	//存储账号
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+3+account_len+1,password_len);	//存储密码长度
	AT24C64_Write(FINGER_FUNC_ADDR*index+3+account_len+2,password,password_len);	//存储密码
}

/**
 * @brief		保存快捷键
 * @param		index 指纹索引
 * @param		shortcut 控制键：bit7-右Win bit6-右Alt bit5-右Shift bit4-右Ctrl bit3-左Win bit2-左Alt bit1-左Shift bit0- 左Ctrl
 * @param		key 普通键(ASCII码)
 * @param   keyLen 普通键个数，最多6个
 * @date		2023-6-11 10:35:51
 * @return 	NULL
 */
void Func_Store_Shortcut(uint8_t index,uint8_t shortcut,uint8_t *key,uint8_t keyLen)
{
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index,(uint8_t)TYPE_Shortcut);	//存储指令类型
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+1,keyLen);	//快捷键个数
	AT24C64_WriteOneByte(FINGER_FUNC_ADDR*index+3,shortcut);	//存储控制键
	AT24C64_Write(FINGER_FUNC_ADDR*index+4,key,keyLen-1);	//存储普通键	keyLen-1:控制键之外的按键个数
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
	/* 输入密码 */
	
	
	free(password);
	return ERROR_PASS;
}

uint8_t Func_Exe_Account_Password(uint8_t index)
{
	uint8_t account_len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+1);	//获取账号长度
	uint8_t *account = (uint8_t *)malloc(account_len);
	AT24C64_Read(FINGER_FUNC_ADDR*index+3,account,account_len);	//获取账号
	uint8_t password_len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+3+account_len);	//获取密码长度
	uint8_t *password = (uint8_t *)malloc(password_len);
	AT24C64_Read(FINGER_FUNC_ADDR*index+3+account_len+2,account,account_len);
	/* 输入账号、密码 */
	
	
	free(account);
	free(password);
	return ERROR_PASS;
}


uint8_t Func_Exe_Shortcut(uint8_t index)
{
	uint8_t len = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+1);	//快捷键个数=控制键+普通键
	uint8_t key_contral = AT24C64_ReadOneByte(FINGER_FUNC_ADDR*index+3);
	uint8_t key_normal[6] = {0};
	AT24C64_Read(FINGER_FUNC_ADDR*index+4,key_normal,len);
	
	uint8_t * comb_value = Combination_Key(key_contral,key_normal);
	
	SendCommand(comb_value);
	
	return ERROR_PASS;
}






























