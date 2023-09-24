/********************************************************************************
** Form generated from reading UI file 'form_entrance.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ENTRANCE_H
#define UI_FORM_ENTRANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Entrance
{
public:
    QProgressBar *progressBar_connect_status;

    void setupUi(QWidget *Form_Entrance)
    {
        if (Form_Entrance->objectName().isEmpty())
            Form_Entrance->setObjectName(QString::fromUtf8("Form_Entrance"));
        Form_Entrance->resize(362, 89);
        progressBar_connect_status = new QProgressBar(Form_Entrance);
        progressBar_connect_status->setObjectName(QString::fromUtf8("progressBar_connect_status"));
        progressBar_connect_status->setGeometry(QRect(70, 30, 201, 21));
        progressBar_connect_status->setValue(0);

        retranslateUi(Form_Entrance);

        QMetaObject::connectSlotsByName(Form_Entrance);
    } // setupUi

    void retranslateUi(QWidget *Form_Entrance)
    {
        Form_Entrance->setWindowTitle(QApplication::translate("Form_Entrance", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_Entrance: public Ui_Form_Entrance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ENTRANCE_H
