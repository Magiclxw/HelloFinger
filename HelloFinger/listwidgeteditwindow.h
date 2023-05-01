#ifndef LISTWIDGETEDITWINDOW_H
#define LISTWIDGETEDITWINDOW_H

#include <QDialog>

extern QString inputText;

namespace Ui {
class ListWidgetEditWindow;
}

class ListWidgetEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListWidgetEditWindow(QWidget *parent = nullptr);
    ~ListWidgetEditWindow();


private:
    Ui::ListWidgetEditWindow *ui;

signals:
    void btn_ok_Clicked();
private slots:

};

#endif // LISTWIDGETEDITWINDOW_H
