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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_Table;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget_table_state;
    QStackedWidget *stackedWidget;
    QWidget *page_enrollState;
    QHBoxLayout *horizontalLayout_8;
    QFrame *frame_table_state;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_enroll_state;
    QProgressBar *progressBar;
    QWidget *page_windows_password;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_windows_password;
    QPushButton *pushButton_save_windows_password;
    QWidget *page_account_password;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_ap_account;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_ap_password;
    QPushButton *pushButton_save_account_password;
    QWidget *page_password;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_password;
    QWidget *tab_RGB;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_color;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_R;
    QSlider *slider_R;
    QLabel *label_R_value;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_G;
    QSlider *slider_G;
    QLabel *label_G_value;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_B;
    QSlider *slider_B;
    QLabel *label_B_value;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_interval;
    QSlider *slider_interval;
    QLabel *label_interval_value;
    QPushButton *pushButton_save_rgb;
    QWidget *tab_system;

    void setupUi(QMainWindow *Form_MainWindow)
    {
        if (Form_MainWindow->objectName().isEmpty())
            Form_MainWindow->setObjectName(QString::fromUtf8("Form_MainWindow"));
        Form_MainWindow->resize(227, 396);
        Form_MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Form_MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(Form_MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabBarAutoHide(false);
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

        stackedWidget = new QStackedWidget(tab_Table);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_enrollState = new QWidget();
        page_enrollState->setObjectName(QString::fromUtf8("page_enrollState"));
        horizontalLayout_8 = new QHBoxLayout(page_enrollState);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        frame_table_state = new QFrame(page_enrollState);
        frame_table_state->setObjectName(QString::fromUtf8("frame_table_state"));
        frame_table_state->setFrameShape(QFrame::Box);
        frame_table_state->setFrameShadow(QFrame::Raised);
        frame_table_state->setLineWidth(2);
        verticalLayout_6 = new QVBoxLayout(frame_table_state);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_enroll_state = new QLabel(frame_table_state);
        label_enroll_state->setObjectName(QString::fromUtf8("label_enroll_state"));
        label_enroll_state->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_enroll_state);

        progressBar = new QProgressBar(frame_table_state);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setStyleSheet(QString::fromUtf8(""));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(false);

        verticalLayout_6->addWidget(progressBar);


        horizontalLayout_8->addWidget(frame_table_state);

        stackedWidget->addWidget(page_enrollState);
        page_windows_password = new QWidget();
        page_windows_password->setObjectName(QString::fromUtf8("page_windows_password"));
        verticalLayout_4 = new QVBoxLayout(page_windows_password);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_3 = new QWidget(page_windows_password);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_windows_password = new QLineEdit(widget_3);
        lineEdit_windows_password->setObjectName(QString::fromUtf8("lineEdit_windows_password"));
        lineEdit_windows_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_windows_password, 0, 1, 1, 1);

        pushButton_save_windows_password = new QPushButton(widget_3);
        pushButton_save_windows_password->setObjectName(QString::fromUtf8("pushButton_save_windows_password"));

        gridLayout->addWidget(pushButton_save_windows_password, 1, 0, 1, 2);


        verticalLayout_4->addWidget(widget_3);

        stackedWidget->addWidget(page_windows_password);
        page_account_password = new QWidget();
        page_account_password->setObjectName(QString::fromUtf8("page_account_password"));
        verticalLayout_3 = new QVBoxLayout(page_account_password);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget = new QWidget(page_account_password);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_ap_account = new QLineEdit(widget);
        lineEdit_ap_account->setObjectName(QString::fromUtf8("lineEdit_ap_account"));

        horizontalLayout_2->addWidget(lineEdit_ap_account);


        verticalLayout_3->addWidget(widget);

        widget_2 = new QWidget(page_account_password);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_ap_password = new QLineEdit(widget_2);
        lineEdit_ap_password->setObjectName(QString::fromUtf8("lineEdit_ap_password"));
        lineEdit_ap_password->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(lineEdit_ap_password);


        verticalLayout_3->addWidget(widget_2);

        pushButton_save_account_password = new QPushButton(page_account_password);
        pushButton_save_account_password->setObjectName(QString::fromUtf8("pushButton_save_account_password"));

        verticalLayout_3->addWidget(pushButton_save_account_password);

        stackedWidget->addWidget(page_account_password);
        page_password = new QWidget();
        page_password->setObjectName(QString::fromUtf8("page_password"));
        horizontalLayout_3 = new QHBoxLayout(page_password);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget_4 = new QWidget(page_password);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        lineEdit_password = new QLineEdit(widget_4);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_password, 0, 1, 1, 1);

        pushButton_password = new QPushButton(widget_4);
        pushButton_password->setObjectName(QString::fromUtf8("pushButton_password"));

        gridLayout_2->addWidget(pushButton_password, 1, 0, 1, 2);


        horizontalLayout_3->addWidget(widget_4);

        stackedWidget->addWidget(page_password);

        verticalLayout->addWidget(stackedWidget);

        tabWidget->addTab(tab_Table, QString());
        tab_RGB = new QWidget();
        tab_RGB->setObjectName(QString::fromUtf8("tab_RGB"));
        verticalLayout_5 = new QVBoxLayout(tab_RGB);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame_color = new QFrame(tab_RGB);
        frame_color->setObjectName(QString::fromUtf8("frame_color"));
        frame_color->setFrameShape(QFrame::Box);
        frame_color->setFrameShadow(QFrame::Raised);
        frame_color->setLineWidth(3);
        frame_color->setMidLineWidth(0);

        verticalLayout_5->addWidget(frame_color);

        widget_8 = new QWidget(tab_RGB);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_R = new QLabel(widget_8);
        label_R->setObjectName(QString::fromUtf8("label_R"));
        label_R->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        label_R->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_R);

        slider_R = new QSlider(widget_8);
        slider_R->setObjectName(QString::fromUtf8("slider_R"));
        slider_R->setMaximumSize(QSize(110, 16777215));
        slider_R->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 0, 0, 255));"));
        slider_R->setMaximum(255);
        slider_R->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(slider_R);

        label_R_value = new QLabel(widget_8);
        label_R_value->setObjectName(QString::fromUtf8("label_R_value"));
        label_R_value->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_R_value);


        verticalLayout_5->addWidget(widget_8);

        widget_5 = new QWidget(tab_RGB);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_G = new QLabel(widget_5);
        label_G->setObjectName(QString::fromUtf8("label_G"));
        label_G->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        label_G->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_G);

        slider_G = new QSlider(widget_5);
        slider_G->setObjectName(QString::fromUtf8("slider_G"));
        slider_G->setMaximumSize(QSize(110, 16777215));
        slider_G->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(0, 255, 0, 255));"));
        slider_G->setMaximum(255);
        slider_G->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider_G);

        label_G_value = new QLabel(widget_5);
        label_G_value->setObjectName(QString::fromUtf8("label_G_value"));
        label_G_value->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_G_value);


        verticalLayout_5->addWidget(widget_5);

        widget_6 = new QWidget(tab_RGB);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_B = new QLabel(widget_6);
        label_B->setObjectName(QString::fromUtf8("label_B"));
        label_B->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 170);\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        label_B->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_B);

        slider_B = new QSlider(widget_6);
        slider_B->setObjectName(QString::fromUtf8("slider_B"));
        slider_B->setMaximumSize(QSize(110, 16777215));
        slider_B->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(0, 0, 255, 255));"));
        slider_B->setMaximum(255);
        slider_B->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider_B);

        label_B_value = new QLabel(widget_6);
        label_B_value->setObjectName(QString::fromUtf8("label_B_value"));
        label_B_value->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_B_value);


        verticalLayout_5->addWidget(widget_6);

        widget_7 = new QWidget(tab_RGB);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_interval = new QLabel(widget_7);
        label_interval->setObjectName(QString::fromUtf8("label_interval"));
        label_interval->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_interval);

        slider_interval = new QSlider(widget_7);
        slider_interval->setObjectName(QString::fromUtf8("slider_interval"));
        slider_interval->setMaximumSize(QSize(110, 16777215));
        slider_interval->setLayoutDirection(Qt::LeftToRight);
        slider_interval->setStyleSheet(QString::fromUtf8(""));
        slider_interval->setMinimum(10);
        slider_interval->setMaximum(255);
        slider_interval->setValue(10);
        slider_interval->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(slider_interval);

        label_interval_value = new QLabel(widget_7);
        label_interval_value->setObjectName(QString::fromUtf8("label_interval_value"));
        label_interval_value->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_interval_value);


        verticalLayout_5->addWidget(widget_7);

        pushButton_save_rgb = new QPushButton(tab_RGB);
        pushButton_save_rgb->setObjectName(QString::fromUtf8("pushButton_save_rgb"));

        verticalLayout_5->addWidget(pushButton_save_rgb);

        tabWidget->addTab(tab_RGB, QString());
        tab_system = new QWidget();
        tab_system->setObjectName(QString::fromUtf8("tab_system"));
        tabWidget->addTab(tab_system, QString());

        verticalLayout_2->addWidget(tabWidget);

        Form_MainWindow->setCentralWidget(centralwidget);

        retranslateUi(Form_MainWindow);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *Form_MainWindow)
    {
        Form_MainWindow->setWindowTitle(QApplication::translate("Form_MainWindow", "Frame_MainWindow", nullptr));

        const bool __sortingEnabled = listWidget_table_state->isSortingEnabled();
        listWidget_table_state->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_table_state->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Form_MainWindow", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_table_state->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Form_MainWindow", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_table_state->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Form_MainWindow", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_table_state->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Form_MainWindow", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_table_state->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Form_MainWindow", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_table_state->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("Form_MainWindow", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_table_state->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("Form_MainWindow", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_table_state->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("Form_MainWindow", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_table_state->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("Form_MainWindow", "9", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_table_state->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("Form_MainWindow", "10", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_table_state->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("Form_MainWindow", "11", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_table_state->item(11);
        ___qlistwidgetitem11->setText(QApplication::translate("Form_MainWindow", "12", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_table_state->item(12);
        ___qlistwidgetitem12->setText(QApplication::translate("Form_MainWindow", "13", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_table_state->item(13);
        ___qlistwidgetitem13->setText(QApplication::translate("Form_MainWindow", "14", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget_table_state->item(14);
        ___qlistwidgetitem14->setText(QApplication::translate("Form_MainWindow", "15", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget_table_state->item(15);
        ___qlistwidgetitem15->setText(QApplication::translate("Form_MainWindow", "16", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget_table_state->item(16);
        ___qlistwidgetitem16->setText(QApplication::translate("Form_MainWindow", "17", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidget_table_state->item(17);
        ___qlistwidgetitem17->setText(QApplication::translate("Form_MainWindow", "18", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget_table_state->item(18);
        ___qlistwidgetitem18->setText(QApplication::translate("Form_MainWindow", "19", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget_table_state->item(19);
        ___qlistwidgetitem19->setText(QApplication::translate("Form_MainWindow", "20", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget_table_state->item(20);
        ___qlistwidgetitem20->setText(QApplication::translate("Form_MainWindow", "21", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget_table_state->item(21);
        ___qlistwidgetitem21->setText(QApplication::translate("Form_MainWindow", "22", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget_table_state->item(22);
        ___qlistwidgetitem22->setText(QApplication::translate("Form_MainWindow", "23", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget_table_state->item(23);
        ___qlistwidgetitem23->setText(QApplication::translate("Form_MainWindow", "24", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget_table_state->item(24);
        ___qlistwidgetitem24->setText(QApplication::translate("Form_MainWindow", "25", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = listWidget_table_state->item(25);
        ___qlistwidgetitem25->setText(QApplication::translate("Form_MainWindow", "26", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget_table_state->item(26);
        ___qlistwidgetitem26->setText(QApplication::translate("Form_MainWindow", "27", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = listWidget_table_state->item(27);
        ___qlistwidgetitem27->setText(QApplication::translate("Form_MainWindow", "28", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget_table_state->item(28);
        ___qlistwidgetitem28->setText(QApplication::translate("Form_MainWindow", "29", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget_table_state->item(29);
        ___qlistwidgetitem29->setText(QApplication::translate("Form_MainWindow", "30", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget_table_state->item(30);
        ___qlistwidgetitem30->setText(QApplication::translate("Form_MainWindow", "31", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget_table_state->item(31);
        ___qlistwidgetitem31->setText(QApplication::translate("Form_MainWindow", "32", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget_table_state->item(32);
        ___qlistwidgetitem32->setText(QApplication::translate("Form_MainWindow", "33", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidget_table_state->item(33);
        ___qlistwidgetitem33->setText(QApplication::translate("Form_MainWindow", "34", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = listWidget_table_state->item(34);
        ___qlistwidgetitem34->setText(QApplication::translate("Form_MainWindow", "35", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidget_table_state->item(35);
        ___qlistwidgetitem35->setText(QApplication::translate("Form_MainWindow", "36", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = listWidget_table_state->item(36);
        ___qlistwidgetitem36->setText(QApplication::translate("Form_MainWindow", "37", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidget_table_state->item(37);
        ___qlistwidgetitem37->setText(QApplication::translate("Form_MainWindow", "38", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = listWidget_table_state->item(38);
        ___qlistwidgetitem38->setText(QApplication::translate("Form_MainWindow", "39", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidget_table_state->item(39);
        ___qlistwidgetitem39->setText(QApplication::translate("Form_MainWindow", "40", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidget_table_state->item(40);
        ___qlistwidgetitem40->setText(QApplication::translate("Form_MainWindow", "41", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidget_table_state->item(41);
        ___qlistwidgetitem41->setText(QApplication::translate("Form_MainWindow", "42", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidget_table_state->item(42);
        ___qlistwidgetitem42->setText(QApplication::translate("Form_MainWindow", "43", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidget_table_state->item(43);
        ___qlistwidgetitem43->setText(QApplication::translate("Form_MainWindow", "44", nullptr));
        QListWidgetItem *___qlistwidgetitem44 = listWidget_table_state->item(44);
        ___qlistwidgetitem44->setText(QApplication::translate("Form_MainWindow", "45", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidget_table_state->item(45);
        ___qlistwidgetitem45->setText(QApplication::translate("Form_MainWindow", "46", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidget_table_state->item(46);
        ___qlistwidgetitem46->setText(QApplication::translate("Form_MainWindow", "47", nullptr));
        QListWidgetItem *___qlistwidgetitem47 = listWidget_table_state->item(47);
        ___qlistwidgetitem47->setText(QApplication::translate("Form_MainWindow", "48", nullptr));
        QListWidgetItem *___qlistwidgetitem48 = listWidget_table_state->item(48);
        ___qlistwidgetitem48->setText(QApplication::translate("Form_MainWindow", "49", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidget_table_state->item(49);
        ___qlistwidgetitem49->setText(QApplication::translate("Form_MainWindow", "50", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidget_table_state->item(50);
        ___qlistwidgetitem50->setText(QApplication::translate("Form_MainWindow", "51", nullptr));
        QListWidgetItem *___qlistwidgetitem51 = listWidget_table_state->item(51);
        ___qlistwidgetitem51->setText(QApplication::translate("Form_MainWindow", "52", nullptr));
        QListWidgetItem *___qlistwidgetitem52 = listWidget_table_state->item(52);
        ___qlistwidgetitem52->setText(QApplication::translate("Form_MainWindow", "53", nullptr));
        QListWidgetItem *___qlistwidgetitem53 = listWidget_table_state->item(53);
        ___qlistwidgetitem53->setText(QApplication::translate("Form_MainWindow", "54", nullptr));
        QListWidgetItem *___qlistwidgetitem54 = listWidget_table_state->item(54);
        ___qlistwidgetitem54->setText(QApplication::translate("Form_MainWindow", "55", nullptr));
        QListWidgetItem *___qlistwidgetitem55 = listWidget_table_state->item(55);
        ___qlistwidgetitem55->setText(QApplication::translate("Form_MainWindow", "56", nullptr));
        QListWidgetItem *___qlistwidgetitem56 = listWidget_table_state->item(56);
        ___qlistwidgetitem56->setText(QApplication::translate("Form_MainWindow", "57", nullptr));
        QListWidgetItem *___qlistwidgetitem57 = listWidget_table_state->item(57);
        ___qlistwidgetitem57->setText(QApplication::translate("Form_MainWindow", "58", nullptr));
        QListWidgetItem *___qlistwidgetitem58 = listWidget_table_state->item(58);
        ___qlistwidgetitem58->setText(QApplication::translate("Form_MainWindow", "59", nullptr));
        QListWidgetItem *___qlistwidgetitem59 = listWidget_table_state->item(59);
        ___qlistwidgetitem59->setText(QApplication::translate("Form_MainWindow", "60", nullptr));
        QListWidgetItem *___qlistwidgetitem60 = listWidget_table_state->item(60);
        ___qlistwidgetitem60->setText(QApplication::translate("Form_MainWindow", "61", nullptr));
        QListWidgetItem *___qlistwidgetitem61 = listWidget_table_state->item(61);
        ___qlistwidgetitem61->setText(QApplication::translate("Form_MainWindow", "62", nullptr));
        QListWidgetItem *___qlistwidgetitem62 = listWidget_table_state->item(62);
        ___qlistwidgetitem62->setText(QApplication::translate("Form_MainWindow", "63", nullptr));
        QListWidgetItem *___qlistwidgetitem63 = listWidget_table_state->item(63);
        ___qlistwidgetitem63->setText(QApplication::translate("Form_MainWindow", "64", nullptr));
        listWidget_table_state->setSortingEnabled(__sortingEnabled);

        label_enroll_state->setText(QApplication::translate("Form_MainWindow", " \346\263\250\345\206\214\347\212\266\346\200\201", nullptr));
        label_3->setText(QApplication::translate("Form_MainWindow", "\345\274\200\346\234\272\345\257\206\347\240\201", nullptr));
        pushButton_save_windows_password->setText(QApplication::translate("Form_MainWindow", "\344\277\235\345\255\230", nullptr));
        label->setText(QApplication::translate("Form_MainWindow", " \350\264\246\345\217\267", nullptr));
        label_2->setText(QApplication::translate("Form_MainWindow", "\345\257\206\347\240\201", nullptr));
        pushButton_save_account_password->setText(QApplication::translate("Form_MainWindow", "\344\277\235\345\255\230", nullptr));
        label_4->setText(QApplication::translate("Form_MainWindow", " \345\257\206\347\240\201", nullptr));
        pushButton_password->setText(QApplication::translate("Form_MainWindow", "\344\277\235\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Table), QApplication::translate("Form_MainWindow", "\345\212\237\350\203\275", nullptr));
        label_R->setText(QApplication::translate("Form_MainWindow", "R", nullptr));
        label_R_value->setText(QApplication::translate("Form_MainWindow", "0", nullptr));
        label_G->setText(QApplication::translate("Form_MainWindow", "G", nullptr));
        label_G_value->setText(QApplication::translate("Form_MainWindow", "0", nullptr));
        label_B->setText(QApplication::translate("Form_MainWindow", "B", nullptr));
        label_B_value->setText(QApplication::translate("Form_MainWindow", "0", nullptr));
        label_interval->setText(QApplication::translate("Form_MainWindow", " \351\242\221\347\216\207", nullptr));
        label_interval_value->setText(QApplication::translate("Form_MainWindow", "10", nullptr));
        pushButton_save_rgb->setText(QApplication::translate("Form_MainWindow", " \344\277\235\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_RGB), QApplication::translate("Form_MainWindow", "RGB", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_system), QApplication::translate("Form_MainWindow", "\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_MainWindow: public Ui_Form_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_MAINWINDOW_H
