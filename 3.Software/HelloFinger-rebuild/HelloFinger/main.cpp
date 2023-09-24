#include "form_mainwindow.h"
#include "form_entrance.h"
#include <QApplication>
#include "interface.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Frame_MainWindow w;
    //w.show();
    Form_Entrance entrance;

    entrance.show();

    return a.exec();
}
