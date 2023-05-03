#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include <QWidget>

extern uint8_t rec_buffer[20];

#define TABLESTATE  0x10    //索引表状态标志
#define ENROLL      0x11    //注册指纹标志
#define DELETE      0x14    //删除指纹标志
#define HEARTBEAT   0x15    //心跳信息

class MsgHandler
{
public:
    MsgHandler();

};
uint8_t CalcCheckSum(uint8_t *msg);
uint8_t Handler(uint8_t *msg);
void GenerateCmd(uint8_t *data,uint8_t dataLen);
uint8_t GenerateChecksum(uint8_t *cmd,uint8_t cmdLen);
#endif // MSGHANDLER_H
