#ifndef FORM_MAINWINDOW_H
#define FORM_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Form_MainWindow; }
QT_END_NAMESPACE

class Form_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Form_MainWindow(QWidget *parent = nullptr);
    ~Form_MainWindow();

private:
    Ui::Form_MainWindow *ui;
public slots:
    void Slot_Updata_TableState(uint8_t *tableState);
};
#endif // FORM_MAINWINDOW_H
