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
        Form_HideWindow->resize(75, 289);
        horizontalLayout = new QHBoxLayout(Form_HideWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 15, 0, 0);
        listWidget_func = new QListWidget(Form_HideWindow);
        new QListWidgetItem(listWidget_func);
        new QListWidgetItem(listWidget_func);
        new QListWidgetItem(listWidget_func);
        new QListWidgetItem(listWidget_func);
        new QListWidgetItem(listWidget_func);
        new QListWidgetItem(listWidget_func);
        new QListWidgetItem(listWidget_func);
        listWidget_func->setObjectName(QString::fromUtf8("listWidget_func"));
        listWidget_func->setFrameShape(QFrame::NoFrame);
        listWidget_func->setIconSize(QSize(10, 10));

        horizontalLayout->addWidget(listWidget_func);


        retranslateUi(Form_HideWindow);

        QMetaObject::connectSlotsByName(Form_HideWindow);
    } // setupUi

    void retranslateUi(QWidget *Form_HideWindow)
    {
        Form_HideWindow->setWindowTitle(QApplication::translate("Form_HideWindow", "Form", nullptr));

        const bool __sortingEnabled = listWidget_func->isSortingEnabled();
        listWidget_func->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_func->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_func->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_func->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_func->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_func->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_func->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_func->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("Form_HideWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        listWidget_func->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Form_HideWindow: public Ui_Form_HideWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_HIDEWINDOW_H
