#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <QObject>

class System_Init : public QObject
{
    Q_OBJECT
public:
    explicit System_Init(QObject *parent = nullptr);

signals:

};

void File_TableName_Init();
void File_FastStart_Save(uint8_t page,uint8_t index,uint8_t checkStete,QString path);
QString File_FastStart_Read(uint8_t page,uint8_t index);
uint8_t FIle_Fast_Start_Num_Get(uint8_t page,uint8_t index);

#endif // SYSTEM_INIT_H
