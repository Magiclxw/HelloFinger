#include "func_fingerprint.h"
#include "delay.h"
#include "stdlib.h"
#include "string.h"
#include "fpm383c.h"
#include "usart.h"

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
/**
 * @brief		等待应答包
 * @param		ticks	次数
 * @date		2023-3-26 17:30:34
 * @return 	执行状态
 *					- 0 未收到响应
 *					- 其他	等待时间(*0.1ms)
 */
uint16_t WaitForResponse(uint16_t ticks)
{
	for(uint16_t i=0;i<ticks;i++){
		if(RxState == 1){
			RxState = 0;	//清除标志
			return i;
		}
		Delay_us(100);
	}
	return 0;
}

/**
 * @brief		生成协议格式所需的命令头、数据长度和校验和
 * @param		
 * @date		
 * @return 	
 */
uint8_t GenerateFixedCMD(uint8_t *data,uint8_t head)		
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
/**
 * @brief		获取索引表状态信息
 * @param		NULL
 * @date		2023-3-26 17:56:17
 * @return 	执行状态
 *					- 0 获取失败
 *					- 1	获取成功
 */
uint8_t GetTableState(void)			//获取索引表信息
{
	CMD_ReadIndexTable(0);
	
	HAL_UART_Transmit(&FINGER,PS_ReadIndexTable,ReadIndexTableSize,1000);
	
	if(WaitForResponse(1000)){
	//if(RxState == 1){
		//RxState = 0;
		for(int i=10;i<8+10;i++)
		{
			RX_TableState[i-10]=RxData2[i];
		}
		return 1;
	}
	return 0;
}

/**
 * @brief		发送睡眠指令
 * @param		NULL
 * @date		2023年3月26日17:57:51
 * @return 	执行状态
 *					- 0 获取失败
 *					- 1	获取成功
 */
uint8_t Con_Sleep(void)
{
	CMD_Sleep();

	HAL_UART_Transmit(&FINGER,PS_Sleep,SleepSize,1000);

	if(WaitForResponse(1000)){
		if(RxData2[8]==0x03 && RxData2[9]==0x00) return 1;
	}
	
	return 0;
}

/**
 * @brief		自动注册模板
 * @param		*ID	注册ID号
 * @param		NUM	指纹录入次数
 * @param		*PARAM	参数
 * @date		2023-3-26 21:27:42
 * @return 	NULL
 */
void Con_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM)
{
	uint8_t rsp[4] = {0x11,0x01,0x00,0x00};
	
	uint32_t timeout = 0;
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//禁用指纹触摸中断
	
	CMD_AutoEnroll(ID,NUM,PARAM);
	
	HAL_UART_Transmit(&FINGER,PS_AutoEnroll,AutoEnrollSize,1000);	//发送自动注册模板指令
	
	while(1)	//将当前状态发送给上位机
	{
		if(WaitForResponse(1000)){
			if(RxData2[9]==0x00){
				if(RxData2[10]==0x03){		//手指移开
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_LEAVE;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					timeout = 0;
					memset(rsp,0,4);
				}
				
				if(RxData2[10]==0x01){		//放下手指
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_PUT;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					timeout = 0;
					memset(rsp,0,4);
				}

				if(RxData2[10]==0x06)			//录入成功
				{
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_SUCCESS;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					RxState = 0;
					break;
				}
			}else{
				if(RxData2[9]==0x27 && RxData2[10]==0x05){		//指纹重复
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_REPEAT;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					RxState = 0;
				}
				break;
			}
			RxState = 0;
		}
		timeout ++;
		if(timeout >= ENROLL_TIMEOUT){
			rsp[2] = ENROLL_STATE_TIMEOUT;
			rsp[3] = Calc_Checksum(rsp);
			HAL_UART_Transmit(&KEYOUT,rsp,4,100);
			RxState = 0;
			break;
		}
		Delay_ms(1);
	}
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}


void Con_GenerateEnroll()
{
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//禁用指纹触摸中断
	
	
}

/**
 * @brief		自动验证指纹
 * @param		*ID	ID号,0xFFFF:1-N搜索,其他:1-1搜索
 * @param		*PARAM	参数
 * @date		2023-3-26 21:32:07
 * @return 	对比结果
 *					- 0x00 成功
 *					- others	失败原因
 */
uint8_t Con_AutoIdentify(uint8_t *ID,uint8_t *PARAM)
{
	CMD_AutoIdentify(3,ID,PARAM);

	HAL_UART_Transmit(&FINGER,PS_AutoIdentify,AutoIdentifySize,1000);

	if(WaitForResponse(1000)){
		if(RxData2[9]==0x00 && RxData2[10]==0x05)	//对比成功
		{
			
			return 0x00;
		}
	}
	return RxData2[9];
}

/**
 * @brief		指纹模块从 ID 位置 0 开始自动搜索没有注册的空白 ID 号	
 * @param		NULL
 * @date		2023-3-26 21:34:23
 * @return 	对比结果
 *					- 0xFFFF 失败
 *					- others	查找到ID号
 * @note		FPM383C无此功能
 */
uint16_t blanknum;
uint16_t Con_GetDummyTempleteNo(void)
{
	CMD_GetDummyTempleteNo();
	
	HAL_UART_Transmit(&FINGER,PS_GetDummyTempleteNo,GetDummyTempleteNoSize,1000);
	
	if(WaitForResponse(1000)){
		if(RX_GetDummyTempleteNoData[9]==0x00)
		{
			blanknum=RX_GetDummyTempleteNoData[10];
			
			blanknum<<=8;
			
			blanknum|=RX_GetDummyTempleteNoData[11];
			
			return blanknum;
		}
	
	}
	
	return 0xFFFF;
}

/**
 * @brief	控制LED灯状态
 * @param	FUNC:功能码 1：普通呼吸灯	2：闪烁灯	3：常开灯	4：常闭灯
 * @param	startcolor:起始颜色
 * @param	endcolor:结束颜色
 * @param	cycle:循环次数 0：无限循环
 * @date	2023-3-21 21:13:28
 * @return 
 */
uint8_t Con_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t cycle)		//led灯控制
{
	CMD_ControlBLN(FUNC,startcolor,endcolor,cycle);
	
	HAL_UART_Transmit(&FINGER,PS_ControlBLN,ControlBLNSize,1000);
	
	//while(RxState!=1);
	//
	//RxState=0;
	if(WaitForResponse(1000)){
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	获取芯片唯一序列号
 * @param	NULL
 * @date	2023-3-26 21:38:40
 * @return 获取结果
 *					- 0 失败
 *					- 1 成功
 */
uint8_t Con_GetChipSN(void)
{
	CMD_GetChipSN();
	
	HAL_UART_Transmit(&FINGER,PS_GetChipSN,GetChipSNSize,1000);
	
	if(WaitForResponse(1000)){
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
	}
	return 1;
}

/**
 * @brief	发送握手指令
 * @param	NULL
 * @date	2023-3-26 21:39:48
 * @return 握手结果
 *					- 0 失败
 *					- 1 成功
 */
uint8_t Con_HandShake(void)
{
	CMD_HandShake();
	
	HAL_UART_Transmit(&FINGER,PS_HandShake,HandShakeSize,1000);
	
	if(WaitForResponse(1000)){
		
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	发送传感器校验指令
 * @param	NULL
 * @date	2023-3-26 21:41:16
 * @return 校验结果
 *					- 0 失败
 *					- 1 成功
 */
uint8_t Con_CheckSensor(void)
{
	CMD_CheckSensor();
	
	HAL_UART_Transmit(&FINGER,PS_CheckSensor,CheckSensorSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[9]!=0x29)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	发送设置口令指令
 * @param	*passWord 口令
 * @date	2023-3-26 21:42:48
 * @return 口令设置结果
 *					- 0 失败
 *					- 1 成功
 */
uint8_t Con_SetPwd(uint8_t *PassWord)
{
	CMD_SetPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_SetPwd,SetPwdSize,1000);
	
	if(WaitForResponse(1000)){
	
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	发送验证口令指令
 * @param	*passWord 口令
 * @date	2023-3-26 21:43:54
 * @return 口令验证结果
 *					- 0 失败
 *					- 1 成功
 */
uint8_t Con_VfyPwd(uint8_t *PassWord)
{
	CMD_VfyPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_VfyPwd,VfyPwdSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	发送设置设备地址指令
 * @param	*Addr 设备地址
 * @date	2023-3-26 21:46:47
 * @return 设置结果
 *					- 0 失败
 *					- 1 成功
 */
uint8_t Con_SetChipAddr(uint8_t *Addr)
{
	CMD_SetChipAddr(Addr);
	
	HAL_UART_Transmit(&FINGER,PS_SetChipAddr,SetChipAddrSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[6]==0x07 && RxData2[9]==0x00)	//生成地址成功
		{
			return 1;									
		}
	}
	return 0;
}

/**
 * @brief	写记事本
 * @param	Page 记事本页码
 * @param *Content 内容
 * @date	2023-3-26 21:49:04
 * @return 设置结果
 *					- 1 成功
 *					- others 失败原因
 */
uint8_t Con_WriteNotepad(uint8_t Page,uint8_t *Content)
{
	CMD_WriteNotePad(Page,Content);
	
	HAL_UART_Transmit(&FINGER,PS_WriteNotepad,WriteNotepadSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
		
	}
	return RxData2[9];				//收包有错
	
}

/**
 * @brief	读记事本
 * @param	Page 记事本页码
 * @date	2023-3-26 21:51:56
 * @return 读取结果
 *					- 1 成功
 *					- others 失败原因
 */
uint8_t Con_ReadNotepad(uint8_t Page)
{
	CMD_ReadNotepad(Page);
	
	HAL_UART_Transmit(&FINGER,PS_ReadNotepad,ReadNotepadSize,1000);
	
	if(WaitForResponse(1000)){
		
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			for(int i=0;i<32;i++)
			{
				RX_ReadNotepad[i]=RxData2[i+10];
			}
			
			return 1;
		}
	}
		return RxData2[9];
}

/**
 * @brief	删除 flash 数据库中指定 ID 号开始的N 个指纹模板
 * @param	*PageID 指纹库模板号
 * @param N 删除的模板个数
 * @date	2023-3-26 21:54:52
 * @return 删除结果
 *					- 1 成功
 *					- 0 失败
 */
uint8_t Con_DeleteChar(uint8_t *PageID,uint8_t *N)
{
	CMD_DeletChar(PageID,N);
	
	HAL_UART_Transmit(&FINGER,PS_DeletChar,DeletCharSize,1000);
	
	if(WaitForResponse(1000)){
		
		if(RxData2[6] == 0x07 && RxData2[9] == 0x00){		//删除成功
			return 1;
		}
		
	}
	return 0;
}


/**
 * @brief	注册指纹
 * @param	BufferID 模板缓冲区
 * @param PageID 页ID
 * @date	2023-3-26 21:58:43
 * @return 删除结果
 *					- 1 成功
 *					- 0 失败
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
			if(WaitForResponse(1000)){
				if(RxData2[9] == 0x02){
					HAL_UART_Transmit(&KEYOUT,"请放置指纹",10,100);
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
		}
		/* 2、生成特征 */
		while(1){
			HAL_UART_Transmit(&FINGER,PS_GenChar,GenCharSize,100);
			if(WaitForResponse(1000)){
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
	}
	/* 3、合并特征 */
	HAL_UART_Transmit(&FINGER,PS_RegModel,RegModelSize,100);
	if(WaitForResponse(1000)){
		if(RxData2[9] != 0x00){
			return errorcode++;
		}
	}
	HAL_UART_Transmit(&KEYOUT,"比较成功",8,100);
	/* 4、存储模板 */
	HAL_UART_Transmit(&FINGER,PS_StoreChar,StoreCharSize,100);
	if(WaitForResponse(1000)){
		if(RxData2[9] != 0x00){
			if(RxData2[9] == 0x01) HAL_UART_Transmit(&KEYOUT,"收包有错",10,100);
			if(RxData2[9] == 0x0b) HAL_UART_Transmit(&KEYOUT,"Page id超出范围",20,100);
			if(RxData2[9] == 0x18) HAL_UART_Transmit(&KEYOUT,"写flash出错",15,100);
			if(RxData2[9] == 0x31) HAL_UART_Transmit(&KEYOUT,"加密等级不匹配",20,100);
			return errorcode++;
		}
		HAL_UART_Transmit(&KEYOUT,"存储成功",8,100);
	}
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	return 0;
}














