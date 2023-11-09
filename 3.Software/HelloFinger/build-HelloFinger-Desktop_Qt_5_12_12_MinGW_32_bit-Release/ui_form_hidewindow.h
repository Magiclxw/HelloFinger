/********************************************************************************
** Form generated from reading UI file 'form_hidewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_HIDEWINDOW_H
#define UI_FORM_HIDEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_HideWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget_func;

    void setupUi(QWidget *Form_HideWindow)
    {
        if (Form_HideWindow->objectName().isEmpty())
            Form_HideWindow->setObjectName(QString::fromUtf8("Form_HideWindow"));
        Form_HideWindow->resize(68, 250);
        horizontalLayout = new QHBoxLayout(Form_HideWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 15, 0, 0);
        listWidget_func = new QListWidget(Form_HideWindow);
        listWidget_func->setObjectName(QString::fromUtf8("listWidget_func"));
        listWidget_func->setEnabled(true);
        listWidget_func->setFrameShape(QFrame::NoFrame);
        listWidget_func->setIconSize(QSize(50, 50));

        horizontalLayout->addWidget(listWidget_func);


        retranslateUi(Form_HideWindow);

        QMetaObject::connectSlotsByName(Form_HideWindow);
    } // setupUi

    void retranslateUi(QWidget *Form_HideWindow)
    {
        Form_HideWindow->setWindowTitle(QApplication::translate("Form_HideWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_HideWindow: public Ui_Form_HideWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_HIDEWINDOW_H
