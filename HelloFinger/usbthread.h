#ifndef USBTHREAD_H
#define USBTHREAD_H

#include <QThread>

class USBTHREAD : public QThread
{
public:
    explicit USBTHREAD(QObject *parent = nullptr);
    void stop();
    void run();

private:
    volatile bool stopped;

signals:

};

#endif // USBTHREAD_H
