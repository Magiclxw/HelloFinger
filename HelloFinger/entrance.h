#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <QMainWindow>
#include <QTimer>

#define PROTOCOLSTATE    0x00       //协议传输状态
#define TRANSMISSIONSTATE 0x01      //透传状态

#define RECEIVE 0xFE            //指令头，表示上位机下发指令

#define DATALEN 0x01            //数据长度
#define CMDLEN  0x06            //指令长度

#define USB_TRANSMIT 0x01		//透传模式
#define USB_COMMAND	 0x02		//协议传输模式
#define USB_TABLESTATE 0x10     //获取索引表状态
#define USB_ENROLL      0x11    //注册指纹
#define USB_IDENTIFY    0x12    //验证指纹
#define USB_DELETE      0x14

QT_BEGIN_NAMESPACE
namespace Ui { class Entrance; }
QT_END_NAMESPACE

class Entrance : public QMainWindow
{
    Q_OBJECT

public:
    Entrance(QWidget *parent = nullptr);
    ~Entrance();
    uint8_t Command[20];    //下发的指令
    uint8_t GenerateChecksum(uint8_t *cmd,uint8_t cmdLen);
    void GenerateCmd(uint8_t *data,uint8_t dataLen);
    QTimer *cmdtimer = new QTimer;
private:
    Ui::Entrance *ui;

private slots:
    void onDeviceIn(QString VID, QString PID);
    void onDeviceOut(QString VID, QString PID);
};
#endif // ENTRANCE_H
