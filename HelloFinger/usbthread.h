#ifndef USBTHREAD_H
#define USBTHREAD_H

#include <QThread>

#define  REC_BUFFER_LEN 50

typedef struct REC_DATA_FORMAT{
    volatile uint8_t cmd;
    volatile uint8_t data_len;
    volatile uint8_t type;
    volatile uint8_t result;
    volatile uint8_t data[60];
    volatile uint8_t checksum;	//checksum = cmd + data_len + type + result + data[...]
} REC_DATA_FORMAT_t;

class USBTHREAD : public QThread
{
    Q_OBJECT
public:
    explicit USBTHREAD(QObject *parent = nullptr);
    void stop();
//    void start();
    void run();


private:
    volatile bool stopped;

signals:
    void SI_TableStateUpdate();
    void SI_EnrollStateUpdate();
};

#endif // USBTHREAD_H
