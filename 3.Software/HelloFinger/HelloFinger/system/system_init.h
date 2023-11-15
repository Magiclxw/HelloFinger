#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <QObject>

#define AUTHOR_EMAIL    "1353182489@qq.com"
#define AUTHOR_GROUP    "692423608"
#define AUTHOR_DEVELOPER_GROUP  "253617048"
#define SOFTWARE_VERSION    "1.0.0"
#define SOFTWARE_UPDATE_LINK    "https://pan.baidu.com/s/1j0SeBc8MDqTK7zDHDOcD2g?pwd=ihth"

typedef enum ChatAI_Cfg_
{
    ChatAI_Cfg_URL,
    ChatAI_Cfg_KEY,
}ChatAI_Cfg_e;

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
int File_Get_ChatAI_URL(QString* url);
int File_Get_ChatAI_KEY(QByteArray* key);
int File_Set_ChatAI(QString url,QString key);
#endif // SYSTEM_INIT_H
