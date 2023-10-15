#ifndef FORM_HIDEWINDOW_H
#define FORM_HIDEWINDOW_H

#include <QWidget>
#include <QtDebug>
#include <QRect>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QScreen>
#include <QMouseEvent>

enum HIDEPOSATION//隐藏位置
{
    HP_None = 0,
    HP_Top = 1,
    HP_Left = 2,
    HP_Right = 3
};

namespace Ui {
class Form_HideWindow;
}

class Form_HideWindow : public QWidget
{
    Q_OBJECT

public:
    explicit Form_HideWindow(QWidget *parent = nullptr);
    ~Form_HideWindow();
    int iconx = 40;
    int icony = 40;
    bool isWindowInScreen(QPoint pos);
    void hideWindow();
    void showWindow();
    void File_Update_Hidewindow_Content();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::Form_HideWindow *ui;
    int m_screenWidth;
    int m_screenheight;
    bool m_isLMousePress;
    QPoint m_relativePos;
    HIDEPOSATION m_hp;
public slots:
    void Slot_UpdateCheckedItem(int dir);
};

#endif // FORM_HIDEWINDOW_H
