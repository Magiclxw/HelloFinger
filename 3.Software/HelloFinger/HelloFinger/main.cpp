#include "form_mainwindow.h"
#include "form_entrance.h"
#include <QApplication>
#include <QSettings>
#include "interface.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Frame_MainWindow w;
    //w.show();
    Form_Entrance entrance;

    /* 设置开机自启动 */
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.setValue("HelloFinger", QCoreApplication::applicationFilePath());

    QDir dir;
    if (!dir.exists("config")) {
        dir.mkdir("config");
    }
    //entrance.show();

    return a.exec();
}
