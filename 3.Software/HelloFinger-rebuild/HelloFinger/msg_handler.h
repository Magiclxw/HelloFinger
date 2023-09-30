#ifndef MSG_HANDLER_H
#define MSG_HANDLER_H

#include <QObject>

extern  uint8_t TableState[8];

#define HID_CMD_HEAD 0xFE
#define FINGER_MAX_NUM  64

#define CONFIRM_OK												(0x00)	//表示指令执行完毕或OK
#define	CONFIRM_REC_ERROR										(0x01)	//表示数据包接收错误
#define CONFIRM_NO_FINGER										(0x02)	//表示传感器上没有手指
#define CONFIRM_RECORD_FAIL                                     (0x03)	//表示录入指纹图像失败
#define CONFIRM_IMAGE_DRY_LIGHT                                 (0x04)	//表示指纹图像太干、太淡而生不成特征
#define CONFIRM_IMAGE_WET_BREEZING                              (0x05)	//表示指纹图像太湿、太糊而生不成特征
#define CONFIRM_IMAGE_MESS                                      (0x06)	//表示指纹图像太乱而生不成特征
#define CONFIRM_IMAGE_LACK                                      (0x07)	//表示指纹图像正常，但特征点太少（或面积太小）而生不成特征
#define CONFIRM_FINGER_MISS_MATCH                               (0x08)	//表示指纹不匹配
#define CONFIRM_FINGER_SEARCH_FAIL                              (0x09)	//表示没搜索到指纹
#define CONFIRM_FEATURE_MATCH_FAIL                              (0x0A)	//表示特征合并失败
#define CONFIRM_ADDRESS_ERROR                                   (0x0B)	//表示访问指纹库时地址序号超出指纹库范围
#define CONFIRM_LIBRARY_READ_ERROR                              (0x0C)	//表示从指纹库读模板出错或无效
#define CONFIRM_FEATURE_UPLOAD_ERROR                            (0x0D)	//表示上传特征失败
#define CONFIRM_REFUSE_FOLLOW_DATA                              (0x0E)	//表示模组不能接收后续数据包
#define CONFIRM_IMAGE_UPLOAD_FAIL                               (0x0F)	//表示上传图像失败
#define CONFIRM_TEMPLATE_DELETE_FAIL                            (0x10)	//表示删除模板失败
#define CONFIRM_CLEAR_LIBRARY_FAIL                              (0x11)	//表示清空指纹库失败
#define CONFIRM_ENTER_LOW_POWER_MODE_FAIL                       (0x12)	//表示不能进入低功耗状态
#define CONFIRM_CMD_ERROR										(0x13)	//表示口令不正确
#define CONFIRM_RESET_ERROR                                     (0x14)	//表示系统复位失败
#define CONFIRM_GENERATE_IMAGE_ERROR                            (0x15)	//表示缓冲区内没有有效原始图而生不成图像
#define CONFIRM_UPDATE_ERROR                                    (0x16)	//表示在线升级失败
#define CONFIRM_FINGER_NO_REPLACE                               (0x17)	//表示残留指纹或两次采集之间手指没有移动过
#define CONFIRM_FLASH_ERROR                                     (0x18)	//表示读写 FLASH 出错
#define CONFIRM_RANDOM_NUMBER_GENERATE_FAIL                     (0x19)	//随机数生成失败
#define CONFIRM_INVALID_REG_NUMBER                              (0x1A)	//无效寄存器号
#define CONFIRM_REG_CONTENT_ERROR                               (0x1B)	//寄存器设定内容错误号
#define CONFIRM_NOTEBOOK_PAGE_ERROR                             (0x1C)	//记事本页码指定错误
#define CONFIRM_PORT_ERROR                                      (0x1D)	//端口操作失败
#define CONFIRM_AUTO_ENROLL_FAIL                                (0x1E)	//自动注册（enroll）失败
#define CONFIRM_LIBRARY_FULL                                    (0x1F)	//指纹库满
#define CONFIRM_ADDR_ERROR                                      (0x20)	//设备地址错误
#define CONFIRM_PASSWORD_ERROR                                  (0x21)	//密码有误
#define CONFIRM_TEMPLATE_NOT_EMPTY                              (0x22)	//指纹模板非空
#define CONFIRM_TEMPLATE_EMPTY                                  (0x23)	//指纹模板为空
#define CONFIRM_LIBRARY_EMPTY                                   (0x24)	//指纹库为空
#define CONFIRM_ENROLL_TIMES_ERROR                              (0x25)	//录入次数设置错误
#define CONFIRM_TIMEOUT											(0x26)	//超时
#define CONFIRM_FINGER_EXIST                                    (0x27)	//指纹已存在
#define CONFIRM_FINGER_FERTURE_RELATED                          (0x28)	//指纹特征有关联
#define CONFIRM_SENSOR_INIT_FAIL                                (0x29)	//传感器初始化失败
#define CONFIRM_DEV_INFO_NOT_EMPTY                              (0x2A)	//模组信息非空
#define CONFIRM_DEV_INFO_EMPTY                                  (0x2B)	//模组信息为空
#define CONFIRM_OPT_FAIL										(0x2C)	//OTP 操作失败
#define CONFIRM_PRIV_KEY_GENERATE_FAIL                          (0x2D)	//秘钥生成失败
#define CONFIRM_PRIV_KEY_NOT_EXIST                              (0x2E)	//秘钥不存在
#define CONFIRM_SAFE_ALG_EXE_FAIL                               (0x2F)	//安全算法执行失败
#define CONFIRM_SAFE_ALG_RESULT_ERROR                           (0x30)	//安全算法加解密结果有误
#define CONFIRM_FUNC_SECURE_NOT_MATCH                           (0x31)	//功能与加密等级不匹配
#define CONFIRM_PRIV_KEY_LOCK                                   (0x32)	//秘钥已锁定
#define CONFIRM_IMAGE_SMALL                                     (0x33)	//图像面积小

typedef enum USB_PROTOCOL_FORMAT
{
    USB_PROTOCOL_FORMAT_NOUSE0,				  //0x00
    USB_PROTOCOL_FORMAT_MODE_SWITCH,		  //0x01
    USB_PROTOCOL_FORMAT_GET_FW_HW,            //0x02
    USB_PROTOCOL_FORMAT_NOUSE2,               //0x03
    USB_PROTOCOL_FORMAT_NOUSE3,               //0x04
    USB_PROTOCOL_FORMAT_NOUSE4,               //0x05
    USB_PROTOCOL_FORMAT_NOUSE5,               //0x06
    USB_PROTOCOL_FORMAT_NOUSE6,               //0x07
    USB_PROTOCOL_FORMAT_NOUSE7,               //0x08
    USB_PROTOCOL_FORMAT_NOUSE8,               //0x09
    USB_PROTOCOL_FORMAT_NOUSE9,               //0x0A
    USB_PROTOCOL_FORMAT_ENROLL_FINGER,        //0x0B
    USB_PROTOCOL_FORMAT_DELETE_FINGER,    	  //0x0C
    USB_PROTOCOL_FORMAT_SET_FINGER_COLOR,     //0x0D
    USB_PROTOCOL_FORMAT_NOUSE11,			  //0x0E
    USB_PROTOCOL_FORMAT_SET_FINGER_COLOR_PRO, //0x0F
    USB_PROTOCOL_FORMAT_GET_INDEX_LIST,		  //0x10
    USB_PROTOCOL_FORMAT_FUNC_STORE,           //0x11
    USB_PROTOCOL_FORMAT_SET_RGB,              //0x12

}USB_PROTOCOL_FORMAT_e;

typedef struct REC_DATA_FORMAT{
    volatile uint8_t cmd;
    volatile uint8_t data_len;
    volatile uint8_t type;
    volatile uint8_t result;
    volatile uint8_t data[60];
    volatile uint8_t checksum;	//checksum = cmd + data_len + type + result + data[...]
} REC_DATA_FORMAT_t;

class Msg_Handler : public QObject
{
    Q_OBJECT
public:
    explicit Msg_Handler(QObject *parent = nullptr);
    int Comp_CheckSum(uint8_t *msg);
    int Data_Resolve(uint8_t *data);


signals:
    void Signal_Update_TableState();
    void Signal_Update_EnrollState(uint8_t state1,uint8_t state2);
};

#endif // MSG_HANDLER_H
