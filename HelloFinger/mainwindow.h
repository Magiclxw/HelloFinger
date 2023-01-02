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

private:
    Ui::MainWindow *ui;

public slots:
    void SL_TableStateUpdate(void);
    void SL_EnrollStateUpdate(void);
signals:
    void SI_AddFinger(uint8_t pos,uint8_t times,uint8_t *param);
    void SI_FingerDelete(uint8_t ID);
    void SI_FingerRefresh(void);
    void SI_TableStateUpdata_T(void);
};

#endif // MAINWINDOW_H
