#include "func_fingerprint.h"
#include "delay.h"
#include "stdlib.h"
#include "string.h"
#include "fpm383c.h"


extern uint8_t RxData1[100];
extern uint8_t RxData2[100];

uint8_t RX_TableData[44];			//存储接收到的数据
uint8_t RX_TableState[8];			//存储索引表状态信息
uint8_t RX_SleepData[12];
uint8_t RX_AutoEnrollData[14];
uint8_t RX_AutoIdentifyData[17]={0};
uint8_t RX_GetDummyTempleteNoData[14];
uint8_t RX_ControlBLN[12];

uint8_t RX_GetChipSN[32];
uint8_t RX_ReadNotepad[32];

uint8_t USB_CMD[100];		//usb发送指令buffer

uint8_t Calc_Checksum(uint8_t *data)		//计算校验和
{
	uint8_t checksum = 0;
	uint8_t datalenght = data[1];
	for(int i=0;i<datalenght+2;i++){
		checksum += data[i];
	}
	return checksum;
}

uint8_t Cmp_Checksum(uint8_t *data)		//比较校验和
{
	uint8_t checksum = 0;
	uint8_t datalenght = data[1];
	for(int i=0;i<datalenght+1;i++){
		checksum += data[i];
	}
	if(checksum == data[datalenght+1]){
		return 1;
	}else{
		return 0;
	}
}


uint8_t GenerateHeadLenCheck(uint8_t *data,uint8_t head)		//生成协议格式所需的命令头、数据长度和校验和
{
	uint8_t checksum = 0;
	uint8_t length = 0;
	length = sizeof(data) + 3;
	
	USB_CMD[0] = head;
	USB_CMD[1] = length;
	/* 填充数据 */
	for(uint8_t i=2;i<length-1;i++){
		USB_CMD[i] = data[i-2];
	}
	/* 计算校验和 */
	for(uint8_t i=0;i<length-1;i++){
		checksum += USB_CMD[i];
	}
	USB_CMD[length - 1] = checksum;
	
	return length;
}

void GetTableState(void)			//获取索引表信息
{
	CMD_ReadIndexTable(0);
	
	HAL_UART_Transmit(&FINGER,PS_ReadIndexTable,ReadIndexTableSize,1000);
	
	while(RxState!=1);

	for(int i=10;i<8+10;i++)
	{
		RX_TableState[i-10]=RxData2[i];
	}
	
	RxState=0;

}

uint8_t Con_Sleep(void)
{
	CMD_Sleep();

	HAL_UART_Transmit(&FINGER,PS_Sleep,SleepSize,1000);

	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[8]==0x03 && RxData2[9]==0x00){
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		return 1;
	}
	return 0;
}

void Get_Free_ID()
{
	
}

void Con_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM)			//自动注册模板
{
	uint8_t rsp[4] = {0x11,0x01,0x00,0x00};
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//禁用指纹触摸中断
	
	CMD_AutoEnroll(ID,NUM,PARAM);
	
	HAL_UART_Transmit(&FINGER,PS_AutoEnroll,AutoEnrollSize,1000);	//发送自动注册模板指令
	
	while(1)	//将当前状态发送给上位机
	{
		if(RxState == 1){
			if(RxData2[9]==0x00){
				if(RxData2[10]==0x03){		//手指移开
					rsp[0] = 0x11;
					rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_LEAVE;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					memset(rsp,0,4);
				}
				
				if(RxData2[10]==0x01){		//放下手指
					rsp[0] = 0x11;
					rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_PUT;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					memset(rsp,0,4);
				}

				if(RxData2[10]==0x06)			//录入成功
				{
					rsp[0] = 0x11;
					rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_SUCCESS;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					RxState = 0;
					break;
				}
			}else{
				if(RxData2[9]==0x27 && RxData2[10]==0x05){		//指纹重复
					rsp[0] = 0x11;
					rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_REPEAT;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					RxState = 0;
				}
				
				//HAL_UART_Transmit(&KEYOUT,"注册失败",10,100);
				break;
			}
			RxState = 0;
		}
	}
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void Con_GenerateEnroll()
{
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//禁用指纹触摸中断
	
	
}

uint8_t Con_AutoIdentify(uint8_t *ID,uint8_t *PARAM)						//自动验证指纹
{
	uint8_t result=0;
	
	CMD_AutoIdentify(3,ID,PARAM);

	HAL_UART_Transmit(&FINGER,PS_AutoIdentify,AutoIdentifySize,1000);

	while(RxState!=1);
	
	if(RxData2[9]==0x00 && RxData2[10]==0x05)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		HAL_UART_Transmit(&KEYOUT,"验证成功",10,100);
		//UnLock(960,625);
		
		RxState=0;
		
		return 0x00;
	}else{
		return RxData2[9];
	}

}

uint16_t blanknum;
uint16_t Con_GetDummyTempleteNo(void)		//指纹模块从 ID 位置 0 开始自动搜索没有注册的空白 ID 号	FPM383C无此功能
{
	CMD_GetDummyTempleteNo();
	
	HAL_UART_Transmit(&FINGER,PS_GetDummyTempleteNo,GetDummyTempleteNoSize,1000);
	
	while(RxState!=1);
	
	if(RX_GetDummyTempleteNoData[9]==0x00)
	{
		blanknum=RX_GetDummyTempleteNoData[10];
		
		blanknum<<=8;
		
		blanknum|=RX_GetDummyTempleteNoData[11];
		
		RxState=0;
		
		return blanknum;
	}
	
	RxState=0;
	
	return 0;
}

uint8_t Con_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t circle)		//led灯控制
{
	CMD_ControlBLN(FUNC,startcolor,endcolor,circle);
	
	HAL_UART_Transmit(&FINGER,PS_ControlBLN,ControlBLNSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_GetChipSN(void)			//获取芯片唯一序列号
{
	CMD_GetChipSN();
	
	HAL_UART_Transmit(&FINGER,PS_GetChipSN,GetChipSNSize,1000);
	
	while(RxState!=1);
	
	if(RxData2[9]==0x00)
	{
		for(int i=0;i<32;i++)
		{
			RX_GetChipSN[i]=RxData2[i+10];
		}
	}else
	{
		return 0;
	}
	RxState=0;
	
	return 1;
}

uint8_t Con_HandShake(void)				//发送握手指令
{
	CMD_HandShake();
	
	HAL_UART_Transmit(&FINGER,PS_HandShake,HandShakeSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		
		return 1;
	}
	
	return 0;
	
}

uint8_t Con_CheckSensor(void)			//发送传感器校验指令
{
	CMD_CheckSensor();
	
	HAL_UART_Transmit(&FINGER,PS_CheckSensor,CheckSensorSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[9]!=0x29)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_SetPwd(uint8_t *PassWord)				//发送设置口令指令
{
	CMD_SetPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_SetPwd,SetPwdSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_VfyPwd(uint8_t *PassWord)				//发送设置口令指令
{
	CMD_VfyPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_VfyPwd,VfyPwdSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_SetChipAddr(uint8_t *Addr)			//设置设备地址
{
	CMD_SetChipAddr(Addr);
	
	HAL_UART_Transmit(&FINGER,PS_SetChipAddr,SetChipAddrSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;									//生成地址成功
	}
	return 0;
}

uint8_t Con_WriteNotepad(uint8_t Page,uint8_t *Content)			//写记事本
{
	CMD_WriteNotePad(Page,Content);
	
	HAL_UART_Transmit(&FINGER,PS_WriteNotepad,WriteNotepadSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x01)
	{
		return 0;				//收包有错
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x1C)
	{
		return 2;				//记事本页码指定错误
	}
	
}

uint8_t Con_ReadNotepad(uint8_t Page)
{
	CMD_ReadNotepad(Page);
	
	HAL_UART_Transmit(&FINGER,PS_ReadNotepad,ReadNotepadSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		for(int i=0;i<32;i++)
		{
			RX_ReadNotepad[i]=RxData2[i+10];
		}
		
		return 1;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x01)			//收包有错
	{
		return 0;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x1C)			//记事本页码指定错误
	{
		return 2;
	}
	
}

uint8_t Con_DeleteChar(uint8_t *PageID,uint8_t *N)
{
	CMD_DeletChar(PageID,N);
	
	HAL_UART_Transmit(&FINGER,PS_DeletChar,DeletCharSize,1000);
	
	while(RxState!=1);
	
	RxState=0;
	
	if(RxData2[6] == 0x07 && RxData2[9] == 0x00){		//删除成功
		return 1;
	}else if(RxData2[6] == 0x07 && RxData2[9] == 0x10){		//删除失败
		return 0;
	}
	
}


/* 	注册指纹
*/
uint8_t Con_Register(uint8_t BufferID,uint16_t PageID)
{
	uint8_t errorcode = 0;
	CMD_GetImage();		//生成获取指纹指令
	CMD_GenChar(1);		//生成生成特征指令
	CMD_RegModel();		//生成合并特征指令
	CMD_StoreChar(BufferID,PageID);		//生成存储模板指令
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//禁用指纹触摸中断
	//HAL_NVIC_DisableIRQ(USART2_IRQn);	//禁用串口中断
	
	/* 1、获取图像 */
	for(uint8_t i =0;i<4;i++){				//循环4次
		while(1){
			HAL_UART_Transmit(&FINGER,PS_GetImage,GetImageSize,100);
			while(RxState!=1);
			if(RxData2[9] == 0x02){
				HAL_UART_Transmit(&KEYOUT,"请放置指纹",10,100);
				Delay_ms(1000);
			}
			if(RxData2[9] == 0x00){
				HAL_UART_Transmit(&KEYOUT,"获取指纹",10,100);
				break;
			}
			if(RxData2[9] == 0x01){
				HAL_UART_Transmit(&KEYOUT,"收包有错",10,100);
				return errorcode++;
			}
		}
		/* 2、生成特征 */
		while(1){
			HAL_UART_Transmit(&FINGER,PS_GenChar,GenCharSize,100);
			while(RxState!=1);
			if(RxData2[9] != 0x00){
				if(RxData2[9] == 0x01) HAL_UART_Transmit(&KEYOUT,"收包有错",10,100);
				if(RxData2[9] == 0x06) HAL_UART_Transmit(&KEYOUT,"指纹图像乱",10,100);
				if(RxData2[9] == 0x07) HAL_UART_Transmit(&KEYOUT,"特征点太少",10,100);
				if(RxData2[9] == 0x08) HAL_UART_Transmit(&KEYOUT,"特征之间无关联",10,100);
				if(RxData2[9] == 0x0a) HAL_UART_Transmit(&KEYOUT,"合并失败",10,100);
				if(RxData2[9] == 0x15) HAL_UART_Transmit(&KEYOUT,"无原始图",10,100);
				if(RxData2[9] == 0x28) HAL_UART_Transmit(&KEYOUT,"特征之间有关联",10,100);
				return errorcode++;
			}else{
				HAL_UART_Transmit(&KEYOUT,"生成特征成功",12,100);
				break;
			}
		}
	}
	/* 3、合并特征 */
	HAL_UART_Transmit(&FINGER,PS_RegModel,RegModelSize,100);
	while(RxState!=1);
	if(RxData2[9] != 0x00){
		return errorcode++;
	}
	HAL_UART_Transmit(&KEYOUT,"比较成功",8,100);
	/* 4、存储模板 */
	Delay_ms(1000);
	HAL_UART_Transmit(&FINGER,PS_StoreChar,StoreCharSize,100);
	while(RxState!=1);
	if(RxData2[9] != 0x00){
		if(RxData2[9] == 0x01) HAL_UART_Transmit(&KEYOUT,"收包有错",10,100);
		if(RxData2[9] == 0x0b) HAL_UART_Transmit(&KEYOUT,"Page id超出范围",20,100);
		if(RxData2[9] == 0x18) HAL_UART_Transmit(&KEYOUT,"写flash出错",15,100);
		if(RxData2[9] == 0x31) HAL_UART_Transmit(&KEYOUT,"加密等级不匹配",20,100);
		return errorcode++;
	}
	HAL_UART_Transmit(&KEYOUT,"存储成功",8,100);
	
	Delay_ms(1000);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	return 0;
}














