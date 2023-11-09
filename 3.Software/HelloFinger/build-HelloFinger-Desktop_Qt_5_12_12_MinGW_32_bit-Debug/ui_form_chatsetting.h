/********************************************************************************
** Form generated from reading UI file 'form_chatsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_CHATSETTING_H
#define UI_FORM_CHATSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_ChatSetting
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_chatURL;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_chatKEY;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_save_chat_config;
    QPushButton *pushButton_cancel_chat_config;

    void setupUi(QDialog *Form_ChatSetting)
    {
        if (Form_ChatSetting->objectName().isEmpty())
            Form_ChatSetting->setObjectName(QString::fromUtf8("Form_ChatSetting"));
        Form_ChatSetting->resize(252, 154);
        Form_ChatSetting->setFocusPolicy(Qt::NoFocus);
        verticalLayout = new QVBoxLayout(Form_ChatSetting);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(Form_ChatSetting);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_chatURL = new QLineEdit(widget);
        lineEdit_chatURL->setObjectName(QString::fromUtf8("lineEdit_chatURL"));

        horizontalLayout->addWidget(lineEdit_chatURL);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(Form_ChatSetting);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_chatKEY = new QLineEdit(widget_2);
        lineEdit_chatKEY->setObjectName(QString::fromUtf8("lineEdit_chatKEY"));

        horizontalLayout_2->addWidget(lineEdit_chatKEY);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(Form_ChatSetting);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_save_chat_config = new QPushButton(widget_3);
        pushButton_save_chat_config->setObjectName(QString::fromUtf8("pushButton_save_chat_config"));

        horizontalLayout_3->addWidget(pushButton_save_chat_config);

        pushButton_cancel_chat_config = new QPushButton(widget_3);
        pushButton_cancel_chat_config->setObjectName(QString::fromUtf8("pushButton_cancel_chat_config"));

        horizontalLayout_3->addWidget(pushButton_cancel_chat_config);


        verticalLayout->addWidget(widget_3);


        retranslateUi(Form_ChatSetting);

        QMetaObject::connectSlotsByName(Form_ChatSetting);
    } // setupUi

    void retranslateUi(QDialog *Form_ChatSetting)
    {
        Form_ChatSetting->setWindowTitle(QApplication::translate("Form_ChatSetting", "Dialog", nullptr));
        label->setText(QApplication::translate("Form_ChatSetting", "URL", nullptr));
        label_2->setText(QApplication::translate("Form_ChatSetting", "KEY", nullptr));
        pushButton_save_chat_config->setText(QApplication::translate("Form_ChatSetting", "\344\277\235\345\255\230", nullptr));
        pushButton_cancel_chat_config->setText(QApplication::translate("Form_ChatSetting", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_ChatSetting: public Ui_Form_ChatSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_CHATSETTING_H
