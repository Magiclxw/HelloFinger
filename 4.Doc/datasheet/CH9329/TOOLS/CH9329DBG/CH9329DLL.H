//
//****************************************
//**  Copyright  (C)  W.ch  1999-2011   **
//**  Web:  http://www.winchiphead.com  **
//****************************************
//**  DLL for HID interface chip CH9329  **
//**  C, VC6.0                          **
//****************************************
//
// HID应用层接口库  V1.1
// 南京沁恒电子有限公司  作者: zyw@wch.cn 2014.08
// HIDDLL  V1.1 
// 
// 
//

#ifndef		_CH9329_DLL_H
#define		_CH9329_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

/*	BAUD rate setting	*/
#define B300		0x01
#define B600		0x02
#define B1200		0x03
#define B2400		0x04
#define B4800		0x05
#define B9600		0x06
#define B14400      0x07
#define B19200		0x08
#define B28800      0x09
#define B38400		0x0A
#define B57600		0x0B
#define B76800      0x0C
#define B115200 	0x0D

/* Parity define	*/
#define P_ODD		0x01        //奇校验
#define P_EVEN		0x02		//偶校验
#define P_SPC		0x03		//空白位
#define P_NONE		0x04		//无校验

/*	Data bits define		*/
#define BIT_5		0x01			
#define BIT_6		0x02
#define BIT_7		0x03
#define BIT_8		0x04

/* Stop bits define	*/
#define STOP_1		0x01			
#define STOP_2		0x02

//初始化DLL库。
BOOL        WINAPI CH9329DllInt();

//CH9329GetHidGuid获取HID的GUID，用法参考CH9329DBG
//等价于HidD_GetHidGuid,参考MSDN
void        WINAPI CH9329GetHidGuid (void *   HidGuid);

// 根据设备的VID/PID来打开设备
// CH9329OpenDevice成功返回设备句柄，失败返回INVALID_HANDLE_VALUE
HANDLE		WINAPI	CH9329OpenDevice(	unsigned short USB_VID,		        //设备的VID
				        unsigned short USB_PID 								//设备的PID
				        ); 
				        
// 根据设备链接名来打开设备
// CH9329OpenDevice成功返回设备句柄，失败返回INVALID_HANDLE_VALUE
HANDLE	WINAPI	CH9329OpenDevicePath(PCHAR DevicePath       //设备链接名
                        );

BOOL	WINAPI	CH9329GetDevicePath(ULONG DevIndex,         //设备索引号，表示系统中第几个HID设备
                                    PCHAR DevicePath,       //函数返回设备链接名
                                    ULONG DevicePathLen     //DevicePath的缓冲区长度
                                    );				
//等价于HidD_GetAttributes获取VID,PID，版本号,参考MSDN。成功返回TRUE,失败返回FALSE
unsigned long	WINAPI CH9329GetAttributes (HANDLE hDeviceHandle,           //设备句柄
                        unsigned short * pVID,                              //返回设备的VID
                        unsigned short * pPID,                              //返回设备的PID
                        unsigned short * pVer                               //返回设备的版本号
                        );
                
//获取CH9329ReadData和CH9329WriteData一次读写的最大数据长度
//成功返回TRUE，失败返回FALSE
unsigned long	WINAPI	CH9329GetBufferLen(HANDLE hDeviceHandle,	        //设备句柄
				        unsigned short * InputReportLen,					//返回接受数据长度
				        unsigned short * OutputReportLen					//返回发送数据长度
				        );
				
//设置CH9329ReadData和CH9329WriteData读写超时间隔，单位毫秒
void		WINAPI	CH9329SetTimeOut(	HANDLE hDeviceHandle,		        //设备句柄
				        unsigned long ReadTimeOut,							//设置读数据超时间隔
				        unsigned long SendTimeOut							//设置写数据超时间隔
				        );
				
//读一包数据，最大长度为CH9329GetBufferLen返回的InputReportLen-2，由芯片固件决定.
//CH9329读一包数据最大长度为31.成功返回TRUE，失败返回FALSE
unsigned long	WINAPI	CH9329ReadData(	HANDLE hDeviceHandle,		        //设备句柄
				        void * 			ReadBuffer ,						//指向接受数据缓冲区
				        unsigned long * pReadLen,							//返回实际读到的数据长度
				        HANDLE 			hEventObject						//等待事件句柄
				        );
				
//写一包数据，最大长度为CH9329GetBufferLen返回的OutputReportLen-2，由芯片固件决定.
//CH9329写一包数据最大长度为31.成功返回TRUE，失败返回FALSE				
unsigned long	WINAPI	CH9329WriteData(	HANDLE hDeviceHandle,           //设备句柄
				        void * 			SendBuffer,							//指向发送数据缓冲区
				        unsigned long	SentLen,							//要发送数据的长度
				        HANDLE 			hEventObject						//等待事件句柄
				        );
/*
ucRate	: 1=300(ucRate为1时对应波特率300),2=600,3=1200,4=2400,5=4800,6=9600(默认值),7=14400,8=19200,9=28800,10=38400,11=57600,12=76800,13=115200
ucCheck	: 1=奇校验,2=偶校验,3=空白位,4=无校验(默认值)
ucStop	: 1=1位(默认值)，2=2位
ucData	：1=5位，2=6位，3=7位，4=8位(默认值)
*/
//设置波特率，ucInterval为接受数据的超时间隔，如果接受到的数据少于31个，
//并且超过ucInterval时间间隔还没接受到数据，CH9329将打包数据上传给PC
//成功返回TRUE，失败返回FALSE
unsigned long	WINAPI	CH9329SetRate(	HANDLE	hDeviceHandle,	            //设备句柄
					    unsigned char	ucRate,	                            //波特率
					    unsigned char	ucCheck,	                        //校验模式
					    unsigned char	ucStop,	                            //停止位
					    unsigned char	ucData,                             //数据位
					    unsigned char	ucInterval                          //HID接受时的时间间隔，0x10=3MS((默认值)),0x20约等于6MS，,0x30约等于9MS
					    );	
					
/*
CH9329InitThreadData,CH9329GetThreadDataLen,CH9329ClearThreadData,
CH9329ReadThreadData,CH9329StopThread
上面这组函数主要是为了方便读数据操作，建议客户使用这种方式读数据。
CH9329InitThreadData:创建一个线程和私有堆，在线程内部的调用CH9329ReadData读数据，读到的数据缓冲在内部的私有堆中。
CH9329GetThreadDataLen:获取内部缓冲区中数据的长度。
CH9329ReadThreadData:读内部缓冲区中数据。
CH9329ClearThreadData:清空缓冲区所有数据。
CH9329StopThread:停止内部线程读取，并清空内部缓冲区。
*/

//初始化线程和私有堆，成功返回TRUE，失败返回FALSE
unsigned long 	WINAPI	CH9329InitThreadData(HANDLE hDeviceHandle   //设备句柄
                        );
                        
//查询数据，返回线程缓冲区中有多少数据
unsigned long 	WINAPI	CH9329GetThreadDataLen(HANDLE hDeviceHandle  //设备句柄
                        );
//读线程中数据，成功返回TRUE，失败返回FALSE
//注意：ReadLen参数在调用之前为要读取的数据长度，长度不能超过ReadBuffer缓冲的大小，否则会发送内存访问溢出
unsigned long 	WINAPI	CH9329ReadThreadData(HANDLE hDeviceHandle,  //HID设备句柄
                        void * ReadBuffer,                          //缓冲区首地址
                        unsigned long *ReadLen                      //调用之前为要读取的数据长度，返回实际读到的数据长度
                        );
//清空缓冲区数据
void 	        WINAPI	CH9329ClearThreadData(HANDLE hDeviceHandle  //设备句柄
                        );
                        
//停止内部线程读取，并清空内部缓冲区
void 	        WINAPI	CH9329StopThread(HANDLE hDeviceHandle       //设备句柄
                        );

//设置产品描述符信息，请谨慎使用，特别要注意设置新VID/PID时，
//打开设备时，CH9329OpenDevice对应的VID/PID要做相应的修改，否则打开失败。
//成功返回TRUE，失败返回FALSE
unsigned long 	WINAPI	CH9329SetDeviceCfg(HANDLE hDeviceHandle,    //设备句柄
                        unsigned short wVID,                        //设置新的VID
                        unsigned short wPID,                        //设置新的PID
                        unsigned short wPower,                      //设置新的设备电流,50~150 
                        char* strManufacturer,                      //设置新的厂商描述符
                        unsigned long  uMSlen,                      //设置新的厂商描述符长度，最大29
                        char* strProduct,                           //设置新的产品描述符
                        unsigned long  uPSlen,                      //设置新的产品描述符长度，最大29
                        char* strSerialNo,                          //设置新的产品序列号
                        unsigned long  uSSlen                       //设置新的产品序列号长度，最大29
                        );

//设置默认波特率，上电后的默认波特率，不设置时CH9329默认波特率是9600，参数含义参考CH9329SetRate
//成功返回TRUE，失败返回FALSE
unsigned long	WINAPI	CH9329SetDefaultRate(	HANDLE	hDeviceHandle,	    //设备句柄
					    unsigned char	ucRate,	                            //波特率
					    unsigned char	ucCheck,	                        //校验模式
					    unsigned char	ucStop,	                            //停止位
					    unsigned char	ucData,                             //数据位
					    unsigned char	ucInterval                          //HID接受时的时间间隔，0x10=3MS((默认值)),0x20约等于6MS，,0x30约等于9MS
					    );	

//恢复出厂默认设置，使CH9329SetDeviceCfg和CH9329SetDefaultRate的设置无效。
//成功返回TRUE，失败返回FALSE
unsigned long	WINAPI	CH9329ResetToDefault(	HANDLE hDeviceHandle 	        //设备句柄
                        );
					
//设置16位IO口方向，成功返回TRUE，失败返回FALSE
unsigned long 	WINAPI	CH9329SetIODir(HANDLE hDeviceHandle,                //设备句柄
                        unsigned short usDir                                //16位IO口的输入输出设置，对应位：1是输出，0是输入                           
                        );
                        
//设置16位IO口的电平，成功返回TRUE，失败返回FALSE
unsigned long 	WINAPI	CH9329WriteIOData(HANDLE hDeviceHandle,             //设备句柄
                        unsigned short usData                               //16位IO口输出的高低电平设置，对应位：1是输出高电平，0是输出地电平
                        );

//获取16位IO口的引脚电平，成功返回TRUE，失败返回FALSE                        
unsigned long 	WINAPI	CH9329ReadIOData(HANDLE hDeviceHandle,              //设备句柄
                        unsigned short* pData                               //获取到的16位IO口的引脚电平
                        );   

//获取厂商字符串描述符，成功返回TRUE，失败返回FALSE 
//等价于HidD_GetManufacturerString，参考MSDN 
unsigned long 	WINAPI  CH9329GetManufacturerString (HANDLE hDeviceHandle,  //设备句柄
                        void * Buffer,                                      //缓冲区首地址
                        unsigned long BufferLength                          //缓冲区大小
                        );

//获取产品字符串描述符，成功返回TRUE，失败返回FALSE 
//等价于HidD_GetProductString，参考MSDN 
unsigned long 	WINAPI  CH9329GetProductString(HANDLE hDeviceHandle,        //设备句柄
                        void * Buffer,                                      //缓冲区首地址
                        unsigned long BufferLength                          //缓冲区大小
                        );

//获取序列号字符串描述符，成功返回TRUE，失败返回FALSE
//等价于HidD_GetSerialNumberString，参考MSDN
unsigned long 	WINAPI  CH9329GetSerialNumberString(HANDLE hDeviceHandle,   //设备句柄
                        void * Buffer,                                      //缓冲区首地址
                        unsigned long BufferLength                          //缓冲区大小
                        );                                                 


//关闭设备
void 		    WINAPI	CH9329CloseDevice(HANDLE hDeviceHandle              //设备句柄
                        );

#ifdef __cplusplus
}
#endif

#endif		// _CH9329_DLL_H
