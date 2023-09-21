#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void on_keyEvent(QKeyEvent* event);

private:
    Ui::MainWindow *ui;

public slots:
    void SL_TableStateUpdate(void);
    void SL_EnrollStateUpdate(void);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void SL_UpdateRGB(void);

signals:
    void SI_AddFinger(uint8_t pos,uint8_t times,uint8_t param1,uint8_t param2);
    void SI_FingerDelete(uint8_t ID);
    void SI_FingerRefresh(void);
    void SI_TableStateUpdata_T(void);
    void SI_USB_SEND_WindowsPassword(QString password,uint8_t index);
    void SI_USB_SEND_Password(QString password,uint8_t index);
    void SI_USB_SEND_Account_Password(QString account,QString password,uint8_t index);
    void SI_USB_SEND_Breath_RGB(uint8_t color_R,uint8_t color_G,uint8_t color_B,uint8_t interval);
};

#endif // MAINWINDOW_H
