#ifndef FORM_MAINWINDOW_H
#define FORM_MAINWINDOW_H

#include <QMainWindow>
#include "msg_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Form_MainWindow; }
QT_END_NAMESPACE

#define ADD_FINGER_PARAM_LED_ON 0x01
#define ADD_FINGER_PARAM_PRE_DISPOSE    0x02    //开启预处理
#define ADD_FINGER_PARAM_RETURN_KEY_PROCESS 0x04    //返回关键步骤
#define ADD_FINGER_PARAM_ID_COVER_ENABLE    0x08    //id允许覆盖
#define ADD_FINGER_PARAM_ENROLL_REPEAT_DISABLE  0x10    //不允许指纹重复注册
#define ADD_FINGER_PARAM_ENROLL_FINGER_NO_LEAVE    0x20    //注册过程不要求手指离开

class Form_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    uint8_t Set_color_R;
    uint8_t Set_color_G;
    uint8_t Set_color_B;
    Form_MainWindow(QWidget *parent = nullptr);
    ~Form_MainWindow();
    void on_keyEvent(QKeyEvent* event);
    void File_Update_TableContent(QString path);
    void File_Save_Shortcut();
    void File_Update_QuickStart_Content();
private:
    Ui::Form_MainWindow *ui;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

public slots:
    void Slot_AddFinger(void);
    void Slot_EnrollState(uint8_t state1,uint8_t state2);
    void Slot_DeleteFinger(void);
    void Slot_RefreshFinger(void);
    void Slot_UpdateIndexTable(void);
    void Slot_SetWindowsPassword(void);
    void Slot_SetPassword(void);
    void Slot_SetAccount_Password(void);
    void Slot_SetBreathRGB(void);
    void Slot_RGB_Display(void);
    void Slot_ChangeItemValue(void);
    void Slot_SaveItemValue(void);
    void Slot_SetShortcut(void);
    void Slot_DeleteQuickStartItem(void);

signals:
    void Signal_AddFinger(uint8_t pos,uint8_t times,uint8_t param1,uint8_t param2);
    void Signal_DeleteFinger(uint8_t id);
    void Signal_RefreshFinger(void);
    void Signal_UpdateIndexTable(void);
    void Signal_SetWindowsPassword(QString password,uint8_t index);
    void Signal_SetPassword(QString password,uint8_t index);
    void Signal_SetAccount_Password(QString account,QString password,uint8_t index);
    void Signal_SetBreathRGB(uint8_t color_R,uint8_t color_G,uint8_t color_B,uint8_t interval);
    void Signal_SetShortcut(uint8_t func,char* key,uint8_t key_len,uint8_t index);
private slots:
    void on_listWidget_task_1_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_table_state_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_task_2_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_task_3_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_task_4_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_task_5_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_task_6_customContextMenuRequested(const QPoint &pos);
};
#endif // FORM_MAINWINDOW_H
