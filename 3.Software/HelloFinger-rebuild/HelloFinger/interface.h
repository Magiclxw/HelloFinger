#ifndef INTERFACE_H
#define INTERFACE_H

#include <QThread>
#include <QDebug>
#include "lib/hidapi.h"
#include "form_mainwindow.h"
#include "msg_handler.h"
#include "hid_function.h"
#include "form_hidewindow.h"

#define PROTOCOL_VID    0x1A86
#define PROTOCOL_PID    0xE129

#define REC_LEN     (100)
#define SEND_LEN    (100)

extern uint8_t rec_buffer[REC_LEN];
extern uint8_t hid_command[SEND_LEN];
extern hid_device *usb_handle;
extern hid_device_info *usb_info;
extern Form_MainWindow *mainwindow;

class Interface : public QThread
{
public:
    explicit Interface(QObject *parent = nullptr);
    void stop();
    void run();
private:
    volatile bool stopped;
};

#endif // INTERFACE_H
