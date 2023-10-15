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
uint8_t File_Fast_Start_Num_Get(uint8_t page,uint8_t index);
void File_HideWindow_Content_Save(QString path,uint8_t index);
QString File_HideWindow_Item_Read(uint8_t index);
uint8_t File_HideWindow_ItemNum_Get(void);

#endif // SYSTEM_INIT_H
