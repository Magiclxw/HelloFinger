/********************************************************************************
** Form generated from reading UI file 'form_enrollstate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ENROLLSTATE_H
#define UI_FORM_ENROLLSTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_EnrollState
{
public:

    void setupUi(QWidget *Form_EnrollState)
    {
        if (Form_EnrollState->objectName().isEmpty())
            Form_EnrollState->setObjectName(QString::fromUtf8("Form_EnrollState"));
        Form_EnrollState->resize(320, 240);

        retranslateUi(Form_EnrollState);

        QMetaObject::connectSlotsByName(Form_EnrollState);
    } // setupUi

    void retranslateUi(QWidget *Form_EnrollState)
    {
        Form_EnrollState->setWindowTitle(QApplication::translate("Form_EnrollState", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_EnrollState: public Ui_Form_EnrollState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ENROLLSTATE_H
