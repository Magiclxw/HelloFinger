QT       += core gui
QT      += winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form_enrollstate.cpp \
    form_entrance.cpp \
    form_mainwindow.cpp \
    hid_function.cpp \
    interface.cpp \
    main.cpp \
    msg_handler.cpp \
    usb_listener.cpp

HEADERS += \
    config/sys_config.h \
    form_enrollstate.h \
    form_entrance.h \
    form_mainwindow.h \
    hid_function.h \
    hidapi.h \
    interface.h \
    lib/hidapi.h \
    msg_handler.h \
    usb_listener.h

FORMS += \
    form_enrollstate.ui \
    form_entrance.ui \
    form_mainwindow.ui

include($$PWD/lib/GlobalMouseKey/GlobalMouseKey.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lhidapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lhidapi
else:unix: LIBS += -L$$PWD/lib/ -lhidapi

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
