#include "hid_function.h"
#include <QDebug>
#include "msg_handler.h"
#include "interface.h"
#include "config/sys_config.h"


Hid_Function::Hid_Function(QObject *parent) : QObject(parent)
{

}

/**
*@brief	生成校验和
*@param	-cmd:指令
*@param -cmdLen:指令长度，不包括固定头和固定长度（cmd[0]、cmd[1]）
*@return 校验和
*/
uint8_t GenerateChecksum(uint8_t *cmd,uint8_t cmdLen)
{
    uint8_t checksum = 0;
    for(int i=0;i<cmdLen;i++){
        checksum += cmd[i];
    }
    return checksum;
}

/**
*@brief	生成HID通信指令
*@param	-data:指令原始指令
*@param -dataLen:原始指令长度
*@return 校验和
*@note HID通信第一个字节固定为0x00，第二个字节固定为后续数据长度
*/
int GenerateCmd(uint8_t *data,uint8_t dataLen)
{
    if(dataLen >= SEND_LEN-4)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t checksum = 0;
    hid_command[0] = 0x00;  //HID通信固定起始字节
    hid_command[1] = dataLen + 3;   //HID通信固定字节，通信数据长度
    hid_command[2] = HID_CMD_HEAD;   //协议指令头
    hid_command[3] = dataLen;

    memcpy(&hid_command[4],data,dataLen);

    checksum = GenerateChecksum(&hid_command[2],dataLen+2);     //获取校验位
    hid_command[dataLen+4] = checksum;
    return OPERATE_SUCCESS;
}

/**
*@brief	发送获取索引表指令
*@param	-usb_handle:HID通信句柄
*@return 执行结果
*/
int HID_Get_TableState(hid_device *usb_handle)
{
    if(usb_handle != NULL){
        uint8_t cmd[3] = {USB_PROTOCOL_FORMAT_GET_INDEX_LIST,0x00,0x00};
        GenerateCmd(cmd,3);
        hid_write(usb_handle,hid_command,8);   //发送获取索引表状态指令
        memset(hid_command,0,SEND_LEN);
        return OPERATE_SUCCESS;
    }
    return OPERATE_ERROR_INVALID_PARAMETERS;
}

/**
*@brief	发送注册指纹指令
*@param	-usb_handle:HID通信句柄
*@param -id:注册指纹号
*@param -param1:注册参数1
*@param -param2:注册参数2
*@param -times:注册次数
*@return 执行结果
*/
int HID_Add_Finger(hid_device *usb_handle,uint8_t id,uint8_t param1,uint8_t param2,uint8_t times)
{
    if(usb_handle == NULL || times >4 || id > FINGER_MAX_NUM)
    {
        return  OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t cmd[8] = {USB_PROTOCOL_FORMAT_ENROLL_FINGER,0x00,0x00,0x00,id,times,param1,param2};
    GenerateCmd(cmd,8);
    hid_write(usb_handle,hid_command,13);  //cmd:8 + head:4 + tail:1
    memset(hid_command,0,SEND_LEN);
    return OPERATE_SUCCESS;
}

/* 发送删除指纹指令 */
int HID_Delete_Finger(hid_device *usb_handle,uint8_t id)
{
    if(usb_handle == NULL || id > FINGER_MAX_NUM)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t cmd[7] = {USB_PROTOCOL_FORMAT_DELETE_FINGER,0x00,0x00,0x00,id,0x00,0x01};
    GenerateCmd(cmd,7);
    hid_write(usb_handle,hid_command,12);
    memset(hid_command,0,SEND_LEN);
    HID_Get_TableState(usb_handle);
    return OPERATE_SUCCESS;
}

/**
* @brief	发送设置开机密码指令
* @param	-usb_handle:HID通信句柄
* @param    -fingertype:执行条件(指纹识别成功或指纹识别成功且按键按下)
* @return 	执行状态
*			- 0     发送成功
*			- -1	发送失败
*/
int HID_Send_WindowsPassword(hid_device *usb_handle,Finger_Type_e fingertype,QString password,uint8_t index)
{
    if(usb_handle == NULL || index > FINGER_MAX_NUM)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    QByteArray ba_password = password.toLatin1();
    char *c_password = ba_password.data();
    uint8_t flag = USB_PROTOCOL_FORMAT_FUNC_STORE;
    uint8_t type = 0;
    if(fingertype == FINGER)
    {
        type = TYPE_Windows_Password;
    }
    else
    {
        type = TYPE_KEY_Windows_Password;
    }
    uint8_t len = password.length();    //获取密码长度
    qDebug() << "len = " << len;
    uint8_t *cmd_pack1 = new uint8_t[7];
    cmd_pack1[0] = flag;
    //后续包个数
    cmd_pack1[1] = 0x00;
    cmd_pack1[2] = 0x01;

    cmd_pack1[3] = type;
    cmd_pack1[4] = index;

    cmd_pack1[5] = len;
    cmd_pack1[6] = 0;
    GenerateCmd(cmd_pack1,7);
    delete[] cmd_pack1;
    hid_write(usb_handle,hid_command,12);

    uint8_t *cmd_pack2 = new uint8_t[len+5];
    cmd_pack2[0] = flag;
    //后续包个数
    cmd_pack2[1] = 0x00;
    cmd_pack2[2] = 0x00;

    cmd_pack2[3] = type;
    cmd_pack2[4] = index;

    memcpy(&cmd_pack2[5],c_password,len);
    GenerateCmd(cmd_pack2,5+len);
    delete[] cmd_pack2;

    hid_write(usb_handle,hid_command,len+10);

    return OPERATE_SUCCESS;
}

/**
*@brief	发送设置密码指令
*@param	-usb_handle:HID通信句柄
*@param -fingertype:执行条件(指纹识别成功或指纹识别成功且按键按下)
*@param -password:密码
*@param -index:指纹索引
*@return 执行结果
*/
int HID_Send_Password(hid_device *usb_handle,Finger_Type_e fingertype,QString password,uint8_t index)
{
    if(usb_handle == NULL || index > FINGER_MAX_NUM)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    QByteArray ba_password = password.toLatin1();
    char *c_password = ba_password.data();
    uint8_t flag = USB_PROTOCOL_FORMAT_FUNC_STORE;
    uint8_t type = 0;
    if(fingertype == FINGER)
    {
        type = TYPE_Password;
    }
    else
    {
        type = TYPE_KEY_Password;
    }
    uint8_t len = password.length();    //获取密码长度
    qDebug() << "len = " << len;
    uint8_t *cmd_pack1 = new uint8_t[7];
    cmd_pack1[0] = flag;
    //后续包个数
    cmd_pack1[1] = 0x00;
    cmd_pack1[2] = 0x01;

    cmd_pack1[3] = type;
    cmd_pack1[4] = index;

    cmd_pack1[5] = len;
    cmd_pack1[6] = 0;
    GenerateCmd(cmd_pack1,7);
    delete[] cmd_pack1;
    hid_write(usb_handle,hid_command,12);

    uint8_t *cmd_pack2 = new uint8_t[len+5];
    cmd_pack2[0] = flag;
    //后续包个数
    cmd_pack2[1] = 0x00;
    cmd_pack2[2] = 0x00;

    cmd_pack2[3] = type;
    cmd_pack2[4] = index;

    memcpy(&cmd_pack2[5],c_password,len);
    GenerateCmd(cmd_pack2,5+len);
    delete[] cmd_pack2;

    hid_write(usb_handle,hid_command,len+10);

    return OPERATE_SUCCESS;
}

/**
*@brief	发送设置账号+密码指令
*@param	-usb_handle:HID通信句柄
*@param -fingertype:执行条件(指纹识别成功或指纹识别成功且按键按下)
*@param -account:账号
*@param -password:密码
*@param -index:指纹索引
*@return 执行结果
*/
int HID_Send_Account_Password(hid_device *usb_handle,Finger_Type_e fingertype,QString account,QString password,uint8_t index)
{
    if(usb_handle == NULL || index > FINGER_MAX_NUM || account.length() == 0 || password.length() == 0)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    char * char_account = account.toLatin1().data();
    char * char_password = password.toLatin1().data();
    uint8_t flag = USB_PROTOCOL_FORMAT_FUNC_STORE;
    uint8_t type = 0;
    if(fingertype == FINGER)
    {
        type = TYPE_Account_Password;
    }
    else
    {
        type = TYPE_KEY_Account_Password;
    }

    uint8_t account_len = account.length();
    uint8_t password_len = password.length();
    uint8_t *cmd_pack1 = new uint8_t[7];
    cmd_pack1[0] = flag;
    cmd_pack1[1] = 0x00;
    cmd_pack1[2] = 0x02;
    cmd_pack1[3] = type;
    cmd_pack1[4] = index;
    cmd_pack1[5] = account_len;
    cmd_pack1[6] = password_len;
    GenerateCmd(cmd_pack1,7);
    delete [] cmd_pack1;
    hid_write(usb_handle,hid_command,7+HID_FIXED_LEN);

    uint8_t *cmd_pack2 = new uint8_t[account_len+5];
    cmd_pack2[0] = flag;
    cmd_pack2[1] = 0x00;
    cmd_pack2[2] = 0x01;
    cmd_pack2[3] = type;
    cmd_pack2[4] = index;
    memcpy(&cmd_pack2[5],char_account,account_len);
    GenerateCmd(cmd_pack2,5+account_len);
    delete [] cmd_pack2;
    hid_write(usb_handle,hid_command,account_len+5+HID_FIXED_LEN);

    uint8_t *cmd_pack3 = new uint8_t[password_len+5];
    cmd_pack3[0] = flag;
    cmd_pack3[1] = 0x00;
    cmd_pack3[2] = 0x00;
    cmd_pack3[3] = type;
    cmd_pack3[4] = index;
    memcpy(&cmd_pack3[5],char_password,password_len);
    GenerateCmd(cmd_pack3,5+password_len);
    delete [] cmd_pack3;
    hid_write(usb_handle,hid_command,password_len+5+HID_FIXED_LEN);

    return OPERATE_SUCCESS;
}

/**
*@brief	发送设置快捷键指令
*@param	-usb_handle:HID通信句柄
*@param -fingertype:执行条件(指纹识别成功或指纹识别成功且按键按下)
*@param -func:快捷键序号
*@param -key:快捷键
*@param -key_len:快捷键个数
*@param -index:指纹索引
*@return 执行结果
*/
int HID_Send_Shortcut(hid_device *usb_handle,Finger_Type_e fingertype,uint8_t func,char* key,uint8_t key_len,uint8_t index)
{
    if(usb_handle == NULL || index > FINGER_MAX_NUM || key_len>6)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t flag = USB_PROTOCOL_FORMAT_FUNC_STORE;
    uint8_t type = 0;
    if(fingertype == FINGER)
    {
        type = TYPE_Shortcut;
    }
    else
    {
        type = TYPE_KEY_Shortcut;
    }
    uint8_t *cmd_pack1 = new uint8_t[7];
    cmd_pack1[0] = flag;
    cmd_pack1[1] = 0x00;
    cmd_pack1[2] = 0x01;
    cmd_pack1[3] = type;
    cmd_pack1[4] = index;
    cmd_pack1[5] = key_len+1;
    cmd_pack1[6] = 0x00;
    GenerateCmd(cmd_pack1,7);
    delete [] cmd_pack1;
    hid_write(usb_handle,hid_command,7+HID_FIXED_LEN);

    uint8_t *cmd_pack2 = new uint8_t[key_len+6];
    cmd_pack2[0] = flag;
    cmd_pack2[1] = 0x00;
    cmd_pack2[2] = 0x00;
    cmd_pack2[3] = type;
    cmd_pack2[4] = index;
    cmd_pack2[5] = func;
    memcpy(&cmd_pack2[6],key,key_len);
    GenerateCmd(cmd_pack2,6+key_len);
    delete [] cmd_pack2;
    hid_write(usb_handle,hid_command,key_len+6+HID_FIXED_LEN);
    return OPERATE_SUCCESS;
}

/**
*@brief	发送设置快捷启动指令
*@param	-usb_handle:HID通信句柄
*@param -fingertype:执行条件(指纹识别成功或指纹识别成功且按键按下)
*@param -startID:快捷启动序号
*@param -index:指纹索引
*@return 执行结果
*/
int HID_Send_QuickStart(hid_device *usb_handle,Finger_Type_e fingertype,QUICK_START_e startID,uint8_t index)
{
    if(usb_handle == NULL || index > QUICK_START_MAX)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t flag = USB_PROTOCOL_FORMAT_FUNC_STORE;
    uint8_t type = 0;
    if(fingertype == FINGER)
    {
        type = TYPE_QuickStart;
    }
    else
    {
        type = TYPE_KEY_QuickStart;
    }
    uint8_t *cmd_pack1 = new uint8_t[7];
    cmd_pack1[0] = flag;
    cmd_pack1[1] = 0x00;
    cmd_pack1[2] = 0x00;
    cmd_pack1[3] = type;
    cmd_pack1[4] = index;
    cmd_pack1[5] = startID;
    cmd_pack1[6] = 00;
    GenerateCmd(cmd_pack1,7);
    delete [] cmd_pack1;
    hid_write(usb_handle,hid_command,7+HID_FIXED_LEN);
    return OPERATE_SUCCESS;
}

/**
*@brief	发送设置呼吸灯指令
*@param	-usb_handle:HID通信句柄
*@param -color_R:红色亮度
*@param -color_G:绿色亮度
*@param -color_B:蓝色亮度
*@param -interval:帧间隔
*@return 执行结果
*/
int HID_Send_Breath_RGB(hid_device *usb_handle,uint8_t color_R,uint8_t color_G,uint8_t color_B,uint8_t interval)
{
    if(usb_handle == NULL)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t flag = USB_PROTOCOL_FORMAT_SET_RGB;
    uint8_t *cmd_pack = new uint8_t[7];
    cmd_pack[0] = flag;
    cmd_pack[1] = 0x00;
    cmd_pack[2] = 0x00;
    cmd_pack[3] = color_R;
    cmd_pack[4] = color_G;
    cmd_pack[5] = color_B;
    cmd_pack[6] = interval;
    GenerateCmd(cmd_pack,7);
    delete [] cmd_pack;
    hid_write(usb_handle,hid_command,7+HID_FIXED_LEN);

    return OPERATE_SUCCESS;
}

/**
*@brief	发送设置指纹灯效指令
*@param	-usb_handle:HID通信句柄
*@param -mode:灯效
*@param -startColor:点亮颜色
*@param -stopColor:熄灭颜色
*@param -cycle:循环次数(0:无限循环)
*@return 执行结果
*/
int HID_Send_Finger_RGB(hid_device *usb_handle,uint8_t mode,uint8_t startColor,uint8_t stopColor,uint8_t cycle)
{
    if(usb_handle == NULL)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t flag = USB_PROTOCOL_FORMAT_SET_FINGER_COLOR;
    uint8_t *cmd_pack = new uint8_t[7];
    cmd_pack[0] = flag;
    cmd_pack[1] = 0x00;
    cmd_pack[2] = 0x00;
    cmd_pack[3] = mode;
    cmd_pack[4] = startColor;
    cmd_pack[5] = stopColor;
    cmd_pack[6] = cycle;
    GenerateCmd(cmd_pack,7);
    delete [] cmd_pack;
    hid_write(usb_handle,hid_command,7+HID_FIXED_LEN);

    return OPERATE_SUCCESS;
}

/**
*@brief	获取硬件、固件信息
*@param	-usb_handle:HID通信句柄
*@return 执行结果
*/
int HID_Get_FW_HW_Msg(hid_device *usb_handle)
{
    if(usb_handle == NULL)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t flag = USB_PROTOCOL_FORMAT_GET_FW_HW;
    uint8_t *cmd_pack = new uint8_t[3];
    cmd_pack[0] = flag;
    cmd_pack[1] = 0x00;
    cmd_pack[2] = 0x00;
    GenerateCmd(cmd_pack,3);
    delete [] cmd_pack;
    hid_write(usb_handle,hid_command,3+HID_FIXED_LEN);
    qDebug() << hid_command;
    return OPERATE_SUCCESS;
}


/**
*@brief	设置Aaction按键功能
*@param	-usb_handle:HID通信句柄
*@param -func:功能类型
*@param -action:功能值
*@return 执行结果
*/
int HID_Set_Action_Func(hid_device *usb_handle, uint8_t func,uint8_t action)
{
    if(usb_handle == NULL)
    {
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    uint8_t flag = USB_PROTOCOL_FORMAT_SET_ACTION;
    uint8_t *cmd_pack = new uint8_t[5];
    cmd_pack[0] = flag;
    cmd_pack[1] = 0x00;
    cmd_pack[2] = 0x00;
    cmd_pack[3] = func;
    cmd_pack[4] = action;
    GenerateCmd(cmd_pack,5);
    delete [] cmd_pack;
    hid_write(usb_handle,hid_command,5+HID_FIXED_LEN);
    return OPERATE_SUCCESS;
}






















