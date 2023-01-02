#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include <QWidget>

extern uint8_t rec_buffer[20];

#define TABLESTATE  0x10
#define ENROLL      0x11
#define DELETE      0x14

class MsgHandler
{
public:
    MsgHandler();

};
uint8_t CalcCheckSum(uint8_t *msg);
uint8_t Handler(uint8_t *msg);

#endif // MSGHANDLER_H
