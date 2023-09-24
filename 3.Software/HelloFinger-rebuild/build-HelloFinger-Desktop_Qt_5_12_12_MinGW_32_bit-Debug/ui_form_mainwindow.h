/********************************************************************************
** Form generated from reading UI file 'form_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_MAINWINDOW_H
#define UI_FORM_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_Table;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget_table_state;
    QWidget *widget;
    QWidget *tab_RGB;

    void setupUi(QMainWindow *Form_MainWindow)
    {
        if (Form_MainWindow->objectName().isEmpty())
            Form_MainWindow->setObjectName(QString::fromUtf8("Form_MainWindow"));
        Form_MainWindow->resize(300, 600);
        centralwidget = new QWidget(Form_MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 302, 601));
        tabWidget->setTabPosition(QTabWidget::West);
        tab_Table = new QWidget();
        tab_Table->setObjectName(QString::fromUtf8("tab_Table"));
        verticalLayout = new QVBoxLayout(tab_Table);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget_table_state = new QListWidget(tab_Table);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        new QListWidgetItem(listWidget_table_state);
        listWidget_table_state->setObjectName(QString::fromUtf8("listWidget_table_state"));

        verticalLayout->addWidget(listWidget_table_state);

        widget = new QWidget(tab_Table);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 300));

        verticalLayout->addWidget(widget);

        tabWidget->addTab(tab_Table, QString());
        tab_RGB = new QWidget();
        tab_RGB->setObjectName(QString::fromUtf8("tab_RGB"));
        tabWidget->addTab(tab_RGB, QString());
        Form_MainWindow->setCentralWidget(centralwidget);

        retranslateUi(Form_MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *Form_MainWindow)
    {
        Form_MainWindow->setWindowTitle(QApplication::translate("Form_MainWindow", "Frame_MainWindow", nullptr));

        const bool __sortingEnabled = listWidget_table_state->isSortingEnabled();
        listWidget_table_state->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_table_state->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_table_state->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_table_state->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_table_state->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_table_state->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_table_state->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_table_state->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_table_state->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_table_state->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_table_state->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_table_state->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_table_state->item(11);
        ___qlistwidgetitem11->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_table_state->item(12);
        ___qlistwidgetitem12->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_table_state->item(13);
        ___qlistwidgetitem13->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget_table_state->item(14);
        ___qlistwidgetitem14->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget_table_state->item(15);
        ___qlistwidgetitem15->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget_table_state->item(16);
        ___qlistwidgetitem16->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidget_table_state->item(17);
        ___qlistwidgetitem17->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget_table_state->item(18);
        ___qlistwidgetitem18->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget_table_state->item(19);
        ___qlistwidgetitem19->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget_table_state->item(20);
        ___qlistwidgetitem20->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget_table_state->item(21);
        ___qlistwidgetitem21->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget_table_state->item(22);
        ___qlistwidgetitem22->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget_table_state->item(23);
        ___qlistwidgetitem23->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget_table_state->item(24);
        ___qlistwidgetitem24->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = listWidget_table_state->item(25);
        ___qlistwidgetitem25->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget_table_state->item(26);
        ___qlistwidgetitem26->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = listWidget_table_state->item(27);
        ___qlistwidgetitem27->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget_table_state->item(28);
        ___qlistwidgetitem28->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget_table_state->item(29);
        ___qlistwidgetitem29->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget_table_state->item(30);
        ___qlistwidgetitem30->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget_table_state->item(31);
        ___qlistwidgetitem31->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget_table_state->item(32);
        ___qlistwidgetitem32->setText(QApplication::translate("Form_MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        listWidget_table_state->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_Table), QApplication::translate("Form_MainWindow", "\345\212\237\350\203\275", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_RGB), QApplication::translate("Form_MainWindow", "RGB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_MainWindow: public Ui_Form_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_MAINWINDOW_H
