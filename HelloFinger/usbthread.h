#ifndef USBTHREAD_H
#define USBTHREAD_H

#include <QThread>

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

};

#endif // USBTHREAD_H
