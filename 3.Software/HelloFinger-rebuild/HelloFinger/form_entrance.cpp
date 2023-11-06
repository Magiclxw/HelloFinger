#include "form_entrance.h"
#include "ui_form_entrance.h"
#include "lib/hidapi.h"
#include <lib/GlobalMouseKey/globalmouseevent.h>
#include "lib/GlobalMouseKey/globalkeyevent.h"
#include "interface.h"
#include "usb_listener.h"



Form_Entrance::Form_Entrance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Entrance)
{
    ui->setupUi(this);
    this->hide();
    Interface *usbInterface = new Interface;
    usbInterface->start();

    USB_Listener *usbListener = new USB_Listener(this);
    usbListener->registerDevice(this->winId());
    qApp->installNativeEventFilter(usbListener);

    connect(usbListener,SIGNAL(deviceIn(QString,QString)),this,SLOT(onDeviceIn(QString,QString)));
    connect(usbListener,SIGNAL(deviceOut(QString,QString)),this,SLOT(onDeviceOut(QString,QString)));
}

void Form_Entrance::onDeviceIn(QString VID, QString PID)
{
    qDebug() << "device in";
    usb_handle = NULL;
    usb_info = NULL;
}


void Form_Entrance::onDeviceOut(QString VID, QString PID)
{
    qDebug() << "device out";
    usb_handle = NULL;
    usb_info = NULL;
}
Form_Entrance::~Form_Entrance()
{
    delete ui;
}
