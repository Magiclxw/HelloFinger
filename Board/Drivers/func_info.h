 #ifndef __INFO_H
#define __INFO_H
#include "stm32f1xx.h"
#include "sys_config.h"



typedef enum{
	TYPE_Windows_Password = 1,	//¿ª»úÃÜÂë
  TYPE_Password,							//ÃÜÂë
  TYPE_Account_Password,			//ÕËºÅ+ÃÜÂë
  TYPE_Shortcut								//¿ì½İ¼ü
}CMD_TYPE_t;

void Func_Store_Win_Password(uint8_t index,uint8_t *password,uint8_t len);
void Func_Store_Password(uint8_t index,uint8_t *password,uint8_t len);
void Func_Store_Account_Password(uint8_t index,uint8_t *account,uint8_t account_len,uint8_t *password,uint8_t password_len);
void Func_Store_Shortcut(uint8_t index,uint8_t shortcut,uint8_t *key,uint8_t keyLen);

uint8_t Func_Store(CMD_TYPE_t cmdtype,uint8_t *data);
uint8_t Func_Exe(uint8_t index);
uint8_t Func_Exe_Win_Password(uint8_t index);
uint8_t Func_Exe_Password(uint8_t index);
uint8_t Func_Exe_Account_Password(uint8_t index);
uint8_t Func_Exe_Shortcut(uint8_t index);



#endif

