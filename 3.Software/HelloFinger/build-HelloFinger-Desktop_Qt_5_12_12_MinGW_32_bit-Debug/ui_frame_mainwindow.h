/********************************************************************************
** Form generated from reading UI file 'frame_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAME_MAINWINDOW_H
#define UI_FRAME_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Frame_MainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Frame_MainWindow)
    {
        if (Frame_MainWindow->objectName().isEmpty())
            Frame_MainWindow->setObjectName(QString::fromUtf8("Frame_MainWindow"));
        Frame_MainWindow->resize(800, 600);
        centralwidget = new QWidget(Frame_MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Frame_MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Frame_MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        Frame_MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(Frame_MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Frame_MainWindow->setStatusBar(statusbar);

        retranslateUi(Frame_MainWindow);

        QMetaObject::connectSlotsByName(Frame_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *Frame_MainWindow)
    {
        Frame_MainWindow->setWindowTitle(QApplication::translate("Frame_MainWindow", "Frame_MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Frame_MainWindow: public Ui_Frame_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAME_MAINWINDOW_H
