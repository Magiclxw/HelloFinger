#ifndef __APP_TASK_KEY_H
#define __APP_TASK_KEY_H

#include "sys_config.h"
#include "drv_ch9329.h"
#include "sys.h"


#define TASK_SIDEBAR_CONTROL_SIZE	(100)
#define TASK_SIDEBAR_CONTROL_PRIORITY	(3)
#define TASK_ACTION_KEY_SIZE	(100)
#define TASK_ACTION_KEY_PRIORITY	(6)
#define TASK_NORMAL_KEY_SIZE	(100)
#define TASK_NORMAL_KEY_PRIORITY	(4)
#define TASK_JOYCON_KEY_SIZE	(100)
#define TASK_JOYCON_KEY_PRIORITY	(4)

typedef enum ACTION_KEY_FUNC_
{
	ACTION_KEY_FUNC_POWER = 1,
	ACTION_KEY_FUNC_MEDIA,
	ACTION_KEY_FUNC_CHAT,
}ACTION_KEY_FUNC_e;


int ENCODER_KeyNotifyFromISR(void);
int Action_KeyNotifyFromISR(void);
int Normal_KeyNotifyFromISR(void);
int Joycon_KeyNotifyFromISR(void);

int Task_Sidebar_CTLCreate(void);
int Task_Action_KEY_CTLCreate(void);
int Task_Normal_KEY_CTLCreate(void);
int Task_Joycon_KEY_CTLCreate(void);

#endif
