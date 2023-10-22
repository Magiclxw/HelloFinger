#include "drv_ch9329.h"

static void CH9329_Data_Format_Init(void);

CMD_FORMAT_t g_cmd_format = {0};
CMD_GENERAL_KEY_DATA_t g_general_key = {0};
CMD_MEDIA_KEY_DATA_t g_media_key = {0};
CMD_POWER_KEY_DATA_t g_power_key = {0};

uint8_t CH9329_CONFIG[50] = 
{
	CFG_WORKMODE_SOFT_0,
	CFG_SERIALMODE_HARD_0,
	CFG_ADDR,
	CFG_BAUD1,
	CFG_BAUD2,
	CFG_BAUD3,
	CFG_BAUD4,
	0x00,
	0x00,
	CFG_PACK_INTERVAL1,
	CFG_PACK_INTERVAL2,
	CFG_VID1,
	CFG_VID2,
	CFG_PID1,
	CFG_PID2,
	CFG_UPLOAD_INTERVAL1,
	CFG_UPLOAD_INTERVAL2,
	CFG_KEY_RELASE_DELAY1,
	CFG_KEY_RELASE_DELAY2,
	CFG_AUTOENTER,
	CFG_ENTER_SYMBOL1_1,
	CFG_ENTER_SYMBOL1_2,
	CFG_ENTER_SYMBOL1_3,
	CFG_ENTER_SYMBOL1_4,
	CFG_ENTER_SYMBOL2_1,
	CFG_ENTER_SYMBOL2_2,
	CFG_ENTER_SYMBOL2_3,
	CFG_ENTER_SYMBOL2_4,
	CFG_FILITER_START1,
	CFG_FILITER_START2,
	CFG_FILITER_START3,
	CFG_FILITER_START4,
	CFG_FILITER_STOP1,
	CFG_FILITER_STOP2,
	CFG_FILITER_STOP3,
	CFG_FILITER_STOP4,
	CFG_STR_EN_FLAG,
	CFG_KEY_FLAST_UPLOAD_FLAG,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00};
//uint8_t CH9329_CONFIG[50] = {0x00,0x80,0x00,0x00,0x00,0x25,0x80,0x08,0x00,0x00,
//														 0x03,0x86,0x1A,0x29,0xE1,0x00,0x00,0x00,0x01,0x00,
//														 0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	 
/**   完整数组末尾一定要加0x0A!!!!!!!!!!!*/


/**-------------------------------------多媒体部分--------------------------------------------------------------*/
////电源控制部分
//uint8_t 					SLEEP									[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x82,0x8A,0xFF,0x0D,0x0A};							//睡眠
//uint8_t 					Power									[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x81,0x89,0xFF,0x0D,0x0A};							//关机？
//uint8_t 					WakeUp								[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x84,0x8C,0xFF,0x0D,0x0A};							//唤醒
//uint8_t 					up										[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x00,0x08,0xFF,0x0D,0x0A};							//电源控制按键释放
//
////多媒体控制部分
//uint8_t 					VolumeDec							[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x02,0x00,0x00,0x0D,0xFF,0x0D,0x0A};		//降低音量 最后两字节是0D 0A !!!!!!
//uint8_t 					VolumeInc							[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x01,0x00,0x00,0x0C,0xFF,0x0D,0x0A};		//提升音量
//uint8_t 					Mute									[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x04,0x00,0x00,0x0F,0xFF,0x0D,0x0A};		//静音
//uint8_t 					Calculator						[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x04,0x0F,0xFF,0x0D,0x0A};		//计算器
//uint8_t 					EMail									[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x01,0x00,0x0C,0xFF,0x0D,0x0A};		//邮箱
//uint8_t 					Search								[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x02,0x00,0x0D,0xFF,0x0D,0x0A};		//搜索
//uint8_t 					Explorer							[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x02,0x0D,0xFF,0x0D,0x0A};		//浏览器
//uint8_t 					ScreenSave						[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x08,0x13,0xFF,0x0D,0x0A};		//浏览器
//
////按键释放
const uint8_t						KeyRelease						[14]							={0x57,0xAB,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C};
/**-------------------------------------------------------------------------------------------------------------*/

const uint8_t ASCII_SEQ[127][2] = 
{/* ctl	key */
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x00},
	{NO_CTRL,KEY_Space},
	{L_SHIFT,KEY_Exclamation						},
	{L_SHIFT,KEY_DoubleQuotationMarks   },
	{L_SHIFT,KEY_Well                   },
	{L_SHIFT,KEY_Dollar                 },	
	{L_SHIFT,KEY_Percent                },	
	{L_SHIFT,KEY_And                    },	
	{NO_CTRL,KEY_SingleQuotes					  },	
	{L_SHIFT,KEY_LeftParenthesis        },	
	{L_SHIFT,KEY_RightParenthesis       },	
	{L_SHIFT,KEY_Star                   },	
	{L_SHIFT,KEY_Plus                   },	
	{NO_CTRL,KEY_Comma								  },	
	{NO_CTRL,KEY_Line                   },	
	{NO_CTRL,KEY_Point								  },	
	{NO_CTRL,KEY_ObliqueLine					  },	
	{NO_CTRL,KEY_Zero                   },	
	{NO_CTRL,KEY_One                    },	
	{NO_CTRL,KEY_Two                    },	
	{NO_CTRL,KEY_Three                  },	
	{NO_CTRL,KEY_Four                   },	
	{NO_CTRL,KEY_Five                   },	
	{NO_CTRL,KEY_Six                    },	
	{NO_CTRL,KEY_Seven                  },	
	{NO_CTRL,KEY_Eight                  },	
	{NO_CTRL,KEY_Nine                   },	
	{L_SHIFT,KEY_Colon                  },	
	{NO_CTRL,KEY_Semicolon						  },	
	{L_SHIFT,KEY_LeftAngleBracket       },	
	{NO_CTRL,KEY_Equal                  },	
	{L_SHIFT,KEY_RightAngleBracket      },	
	{L_SHIFT,KEY_QuestionMark						},	
	{L_SHIFT,KEY_At                     },	
	{L_SHIFT,KEY_A                      },	
	{L_SHIFT,KEY_B                      },	
	{L_SHIFT,KEY_C                      },	
	{L_SHIFT,KEY_D                      },	
	{L_SHIFT,KEY_E                      },	
	{L_SHIFT,KEY_F                      },	
	{L_SHIFT,KEY_G                      },	
	{L_SHIFT,KEY_H                      },	
	{L_SHIFT,KEY_I                      },	
	{L_SHIFT,KEY_J                      },	
	{L_SHIFT,KEY_K                      },	
	{L_SHIFT,KEY_L                      },	
	{L_SHIFT,KEY_M                      },	
	{L_SHIFT,KEY_N                      },	
	{L_SHIFT,KEY_O                      },	
	{L_SHIFT,KEY_P                      },	
	{L_SHIFT,KEY_Q                      },	
	{L_SHIFT,KEY_R                      },	
	{L_SHIFT,KEY_S                      },	
	{L_SHIFT,KEY_T                      },	
	{L_SHIFT,KEY_U                      },	
	{L_SHIFT,KEY_V                      },	
	{L_SHIFT,KEY_W                      },	
	{L_SHIFT,KEY_X                      },	
	{L_SHIFT,KEY_Y                      },	
	{L_SHIFT,KEY_Z                      },	
	{NO_CTRL,KEY_LeftSquareBrackets		  },	
	{NO_CTRL,KEY_Backlash								},	
	{NO_CTRL,KEY_RightSquareBrackets	  },	
	{L_SHIFT,KEY_UpAngleBrackets        },	
	{L_SHIFT,KEY_DownLine               },	
	{NO_CTRL,KEY_Pie                    },	
	{NO_CTRL,KEY_a										  },	
	{NO_CTRL,KEY_b										  },	
	{NO_CTRL,KEY_c										  },	
	{NO_CTRL,KEY_d										  },	
	{NO_CTRL,KEY_e										  },	
	{NO_CTRL,KEY_f										  },	
	{NO_CTRL,KEY_g										  },	
	{NO_CTRL,KEY_h										  },	
	{NO_CTRL,KEY_i										  },		
  {NO_CTRL,KEY_j										  },
  {NO_CTRL,KEY_k											},	  
  {NO_CTRL,KEY_l											},	  
  {NO_CTRL,KEY_m											},	  
  {NO_CTRL,KEY_n											},	  
  {NO_CTRL,KEY_o											},	  
  {NO_CTRL,KEY_p											},	  
  {NO_CTRL,KEY_q                 			},     
  {NO_CTRL,KEY_r											},	  
  {NO_CTRL,KEY_s											},	  
  {NO_CTRL,KEY_t											},	  
  {NO_CTRL,KEY_u											},	  
  {NO_CTRL,KEY_v											},	  
  {NO_CTRL,KEY_w											},	  
  {NO_CTRL,KEY_x											},	  
  {NO_CTRL,KEY_y											},	  
  {NO_CTRL,KEY_z											},	  
  {L_SHIFT,KEY_Leftbrace         			},     
  {L_SHIFT,KEY_PerpendicularLine			},		
  {L_SHIFT,KEY_Rightbrace        			},     
  {L_SHIFT,KEY_Wave              			},
};


const uint32_t MEDIA_KEY_SEQ[25] = 
{
	KEY_RELEASE,
	KEY_MEDIA,
	KEY_EXPLORER,
	KEY_CALCULATOR,
	KEY_SCREEN_SAVE,
	KEY_MY_COMPUTER,
	KEY_MINIMIZE,
	KEY_RECORD,
	KEY_REWIND,
	KEY_EMAIL,
	KEY_WB_SEARCH,
	KEY_WB_FAVORITES,
	KEY_WB_HOME,
	KEY_WB_BACK,
	KEY_WB_FORWARD,
	KEY_WB_STOP,
	KEY_REFRESH,
	KEY_VOLUME_ADD,
	KEY_VOLUME_SUM,
	KEY_MUTE,
	KEY_PLAY_PAUSE,
	KEY_NEXT_TRACK,
	KEY_PREV_TRACK,
	KEY_CD_STOP,
	KEY_EJECT
};

const uint8_t POWER_KEY_SEQ[4] = 
{
	KEY_RELEASE,
	KEY_POWER,
	KEY_SLEEP,
	KEY_WAKE_UP
};
/********************************************功能配置**************************************************/

void CH9329_Init(void)		//CH9329引脚初始化
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	/* 复位引脚默认低电平 */
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);		//SET脚默认低电平
	
	/* 复位引脚配置 */
	gpio.Mode=GPIO_MODE_OUTPUT_PP;
	gpio.Pin=GPIO_PIN_12;
	gpio.Pull=GPIO_PULLDOWN;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);
	
	/* SET脚配置 */
	gpio.Mode=GPIO_MODE_OUTPUT_PP;
	gpio.Pin=GPIO_PIN_5;
	gpio.Pull=GPIO_PULLDOWN;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
	/* 工作模式配置为协议传输 */
	//SET_EN;
	//CH9329_WorkMode_Config(CFG_WORKMODE_SOFT_0);
	//CH9329_SerialMode_Config(CFG_SERIALMODE_SOFT_0);
	//CH9329_Set_Cfg();
	//SET_DEN;
	
	CH9329_Data_Format_Init();
}

/* 初始化结构体 */
static void CH9329_Data_Format_Init(void)
{
	g_cmd_format.head1 = 0x57;
	g_cmd_format.head2 = 0xAB;
	g_cmd_format.addr = 0x00;
	g_general_key.null = 0x00;
	g_media_key.report_id = 0x02;
	g_power_key.report_id = 0x01;
}

void CH9329_Reset(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
	delay_ms(1000);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
}

void CH9329_WorkMode_Config(uint8_t workmode)
{
	CH9329_CONFIG[CH9329_CONFIG_INDEX_WORK_MODE] = workmode;
}

void CH9329_SerialMode_Config(uint8_t serialmode)
{
	CH9329_CONFIG[CH9329_CONFIG_INDEX_PORT_MODE] = serialmode;
}

void CH9329_SerialAddr_Config(uint8_t addr)
{
	CH9329_CONFIG[CH9329_CONFIG_INDEX_ADDR] = addr;
}

void CH9329_SerialBaudRate_Config(uint8_t* baudrate)
{
	CH9329_CONFIG[CH9329_CONFIG_INDEX_BAUD_1] = baudrate[0];
	CH9329_CONFIG[CH9329_CONFIG_INDEX_BAUD_2] = baudrate[1];
	CH9329_CONFIG[CH9329_CONFIG_INDEX_BAUD_3] = baudrate[2];
	CH9329_CONFIG[CH9329_CONFIG_INDEX_BAUD_4] = baudrate[3];
}

void CH9329_SerialInterval_Config(uint8_t* interval)
{
	CH9329_CONFIG[CH9329_CONFIG_INDEX_PACK_INTERVAL_1] = interval[0];
	CH9329_CONFIG[CH9329_CONFIG_INDEX_PACK_INTERVAL_2] = interval[1];
}

void CH9329_Vid_Pid_Config(uint16_t vid,uint16_t pid)
{
	CH9329_CONFIG[CH9329_CONFIG_INDEX_VID_1] = vid;
	CH9329_CONFIG[CH9329_CONFIG_INDEX_VID_2] = vid>>8;
	CH9329_CONFIG[CH9329_CONFIG_INDEX_PID_1] = pid;
	CH9329_CONFIG[CH9329_CONFIG_INDEX_PID_2] = pid>>8;
}

void CH9329_Get_Cfg(void)	//CH9329获取配置信息
{
	uint8_t cmd[6] = {0x57,0xAB,0x00,CMD_GET_PARA_CFG,0x00};
	uint8_t checksum = 0;
	for(uint8_t i=0;i<5;i++){
		checksum+=cmd[i];
	}
	cmd[5] = checksum;
	SET_EN;
	delay_ms(500);
	HAL_UART_Transmit(&huart1,cmd,6,1000);
	delay_ms(500);
	SET_DEN;
}

void CH9329_Set_Cfg(void)	//CH9329参数配置
{
	uint8_t cmd[56] = {0x57,0xAB,0x00,CMD_SET_PARA_CFG,0x32};
	uint8_t checksum = 0;
	for(uint8_t i=0;i<55;i++){
		cmd[i+5] = CH9329_CONFIG[i];
		checksum += cmd[i];
	}
	cmd[55] = checksum;
	HAL_UART_Transmit(&huart1,cmd,56,1000);
	delay_ms(2000);
	CH9329_Reset();
}

void CH9329_Get_Info(void)
{
	uint8_t cmd[6] = {0x57,0xAB,0x00,CMD_GET_INFO,0x00};
	uint8_t checksum = 0;
	checksum = CH9329_CAL_SUM(cmd,4);
	cmd[5] = checksum;
	HAL_UART_Transmit(&huart1,cmd,6,1000);
}



/************************************************数据处理***********************************************/
void CH9329_Index_to_Ascii(uint8_t *ascii)
{
	uint16_t len = 0;	//记录数据长度
	static uint8_t ascii_value[100] = {0};
	len=strlen((char*)ascii);
	for(int i=0;i<len;i++){
		ascii_value[i]=(char)ascii[i];
	}
}

uint8_t CH9329_CAL_SUM(uint8_t *cmd,uint8_t len)
{
	uint8_t sum = 0;
	for(uint8_t i=0;i<len;i++)
	{
		sum += cmd[i];
	}
	return sum;
}

/**
* @brief		生成按键指令，根据不同的type，key_value和含义不同
* @param		- type	按键类型
*	@param		- key_value	ASCII码、多媒体按键索引、电源功能按键索引
* @date			2023-7-29 09:10:51
* @return 	NULL
* @note	if(type == KEY_TYPE_GENERAL_KEY)	key_value = ASCII码
*				if(type == KEY_TYPE_MEDIA_KEY)	key_value = 多媒体按键索引
*				if(type == KEY_TYPE_POWER_KEY)	key_value = 电源功能按键索引
*/
void CH9329_Generate_KEY_CMD(KEY_TYPE_e type,uint8_t key_contral,char key_value)
{
	switch (type)
	{
		case KEY_TYPE_ASCII_KEY:	//普通按键
		{
			g_cmd_format.cmd = CMD_SEND_KB_GENERAL_DATA;
			g_cmd_format.len = 0x08;
			//g_cmd_format.data = (uint8_t*)&g_general_key;
			//memcpy((uint8_t*)&g_cmd_format.data,(uint8_t*)&g_general_key,8);
			g_general_key.key_ctrl = ASCII_SEQ[key_value][0];
			g_general_key.key1 = ASCII_SEQ[key_value][1];
			g_general_key.key2 = 0x00;
			g_general_key.key3 = 0x00;
			g_general_key.key4 = 0x00;
			g_general_key.key5 = 0x00;
			g_general_key.key6 = 0x00;
			memcpy((uint8_t*)&g_cmd_format.data,(uint8_t*)&g_general_key,CMD_GENERAL_KEY_LEN);
			g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
			break;
		}
		case KEY_TYPE_MEDIA_KEY:	//多媒体按键
		{
			uint32_t m_key = 0;
			g_cmd_format.cmd = CMD_SEND_KB_MEDIA_DATA;
			g_cmd_format.len = 4;
			//g_cmd_format.data = (uint8_t*)&g_media_key;
			m_key = MEDIA_KEY_SEQ[key_value];
			g_media_key.media_key1 = m_key>>16;
			g_media_key.media_key2 = m_key>>8;
			g_media_key.media_key3 = (uint8_t)m_key;
			memcpy((uint8_t*)&g_cmd_format.data,(uint8_t*)&g_media_key,CMD_MEDIA_KEY_LEN);
			g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
			break;
		}
		case KEY_TYPE_POWER_KEY:	//电源功能按键
		{
			g_cmd_format.cmd = KEY_TYPE_POWER_KEY;
			g_cmd_format.len = 2;
			//g_cmd_format.data = (uint8_t*)&g_power_key;
			g_power_key.power_key = POWER_KEY_SEQ[key_value];
			memcpy((uint8_t*)&g_cmd_format.data,(uint8_t*)&g_power_key,CMD_POWER_KEY_LEN);
			g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
			break;
		}
		case KEY_TYPE_FUNC_KEY:
		{
			g_cmd_format.cmd = CMD_SEND_KB_GENERAL_DATA;
			g_cmd_format.len = 0x08;
			g_general_key.key_ctrl = key_contral;
			g_general_key.key1 = (uint8_t)key_value;
			g_general_key.key2 = 0x00;
			g_general_key.key3 = 0x00;
			g_general_key.key4 = 0x00;
			g_general_key.key5 = 0x00;
			g_general_key.key6 = 0x00;
			memcpy((uint8_t*)&g_cmd_format.data,(uint8_t*)&g_general_key,CMD_GENERAL_KEY_LEN);
			g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
			break;
		}
		default : break;
	}
	
}

/* 生成快捷键指令 */
static int CH9329_Generate_Shortcut(uint8_t func_key,char *key,uint8_t key_len)
{
	if(key_len > 6)
	{
		return OPERATE_ERROR_INVALID_PARAMETERS;
	}
	uint8_t *addr = &g_general_key.key1;
	g_cmd_format.cmd = CMD_SEND_KB_GENERAL_DATA;
	g_cmd_format.len = 0x08;
	g_general_key.key_ctrl = func_key;
	g_general_key.key1 = 0x00;
	g_general_key.key2 = 0x00;
	g_general_key.key3 = 0x00;
	g_general_key.key4 = 0x00;
	g_general_key.key5 = 0x00;
	g_general_key.key6 = 0x00;
	for(uint8_t i=0;i<key_len;i++)
	{
		*addr = ASCII_SEQ[key[i]][1];
		addr ++;
	}
	memcpy((uint8_t*)&g_cmd_format.data,(uint8_t*)&g_general_key,CMD_GENERAL_KEY_LEN);
	g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
	
	return OPERATE_SUCCESS;
}


/* 输入字符串 */
void CH9329_Input_Ascii(char *ascii,uint8_t len)
{
	//uint16_t len = strlen(ascii);	//获取字符个数
	for(uint16_t i=0;i<len;i++)
	{
		CH9329_Generate_KEY_CMD(KEY_TYPE_ASCII_KEY,NO_CTRL,ascii[i]);
		HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
		delay_ms(1);
		HAL_UART_Transmit(&huart1,KeyRelease,14,1000);	//释放按键
		delay_ms(1);
	}
}

/* 输入快捷键 */
void CH9329_Input_Shortcut(uint8_t func_key,char *key,uint8_t key_len)
{
	CH9329_Generate_Shortcut(func_key,key,key_len);
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
	delay_ms(1);
	HAL_UART_Transmit(&huart1,KeyRelease,14,1000);	//释放按键
	delay_ms(1);
}

/* 输入功能键 */
void CH9329_Input_Fuc_Key(uint8_t key_contral,uint8_t func_key)
{
	CH9329_Generate_KEY_CMD(KEY_TYPE_FUNC_KEY,key_contral,func_key);
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
	delay_ms(1);
	HAL_UART_Transmit(&huart1,KeyRelease,14,1000);	//释放按键
	delay_ms(1);
}

/* 输入多媒体按键 */
void CH9329_Input_Media_Key(uint8_t key_index)
{
	CH9329_Generate_KEY_CMD(KEY_TYPE_MEDIA_KEY,0x00,key_index);
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
	delay_ms(1);
	HAL_UART_Transmit(&huart1,KeyRelease,14,1000);	//释放按键
	delay_ms(1);
}

/**
* @brief		发送自定义数据包(协议传输)
* @param		- data 数据包
* @param		- len	数据包长度
* @date			2023-7-29 09:28:29
* @return 	NULL
* @note
*/
int Send_HID_Data(uint8_t *data,uint8_t len)
{
	if(len > CH9329_TRANS_MAX_DATA_LEN)
	{
		return OPERATE_ERROR_INVALID_PARAMETERS;
	}
	
	g_cmd_format.cmd = CMD_SEND_MY_HID_DATA;
	g_cmd_format.len = len;
	memcpy((uint8_t*)&g_cmd_format.data,data,len);
	g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
	
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+9,1000);
	
	return OPERATE_SUCCESS;
}


/**
* @brief	绝对鼠标数据包
* @param	step:滚轮滑动步数
* @param	pos_x:x方向移动路径
* @param	pos_y:y方向移动路径
* @param	button:按下按键	0x01:左键，0x02:右键，0x04:中键
* @date		2023-8-8 21:11:19
* @return 
*/
int ABD_Mouse_Ctrl(uint8_t step,uint8_t* pos_x,uint8_t* pos_y,BUTTON_VALUE_e button)
{
	g_cmd_format.cmd = CMD_SEND_MS_ABS_DATA;
	g_cmd_format.len = 7;
	g_cmd_format.data[0] = 0x02;
	g_cmd_format.data[1] = button;
	memcpy((uint8_t*)&g_cmd_format.data[2],pos_x,2);
	memcpy((uint8_t*)&g_cmd_format.data[4],pos_y,2);
	g_cmd_format.data[6] = step;
	g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
	return OPERATE_SUCCESS;
}

/**
* @brief	相对鼠标数据包
* @param	step:滚轮滑动步数
* @param	pos_x:x方向移动路径
* @param	pos_y:y方向移动路径
* @param	button:按下按键	0x01:左键，0x02:右键，0x04:中键
* @date	2023-8-8 21:13:32
* @return 
*/
int REL_Mouse_Ctrl(uint8_t step,uint8_t dir_x,uint8_t dir_y,BUTTON_VALUE_e button)
{
	g_cmd_format.cmd = CMD_SEND_MS_REL_DATA;
	g_cmd_format.len = 5;
	g_cmd_format.data[0] = 0x01;
	g_cmd_format.data[1] = button;
	g_cmd_format.data[2] = dir_x;
	g_cmd_format.data[3] = dir_y;
	g_cmd_format.data[4] = step;
	g_cmd_format.data[g_cmd_format.len] = CH9329_CAL_SUM((uint8_t*)&g_cmd_format,g_cmd_format.len+5);
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
	return OPERATE_SUCCESS;
}

int Quick_Start(char key)
{
	if(key < '0' || key > '5')
	{
		return OPERATE_ERROR_INVALID_PARAMETERS;
	}
	CH9329_Generate_Shortcut(R_WINDOWS|R_CTRL,&key,1);
	HAL_UART_Transmit(&huart1,(uint8_t*)&g_cmd_format,g_cmd_format.len+6,1000);
	delay_ms(1);
	HAL_UART_Transmit(&huart1,KeyRelease,14,1000);	//释放按键
	delay_ms(1);
	return OPERATE_SUCCESS;
}

int CH9329_Key_Release(void)	//发送释放按键指令
{
	HAL_UART_Transmit(&huart1,KeyRelease,14,1000);	//释放按键
}

/**
* @brief	美式键盘、通用键盘切换
* @date	2023-10-14 16:29:56
* @return 
*/
int CH9329_Keyboard_Switch(void)
{
	CH9329_Input_Shortcut(R_SHIFT|R_ALT,NULL,0);
	
}