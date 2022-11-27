#ifndef HIDEWINDOW_H
#define HIDEWINDOW_H

#include <QWidget>

enum HIDEPOSATION//隐藏位置
{
    HP_None = 0,
    HP_Top = 1,
    HP_Left = 2,
    HP_Right = 3
};

namespace Ui {
class HideWindow;
}

class HideWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HideWindow(QWidget *parent = nullptr);
    ~HideWindow();
    int iconx = 40;
    int icony = 40;
    bool isWindowInScreen(QPoint pos);
    void hideWindow();
    void showWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::HideWindow *ui;

    int m_screenWidth;
    int m_screenheight;
    bool m_isLMousePress;
    QPoint m_relativePos;
    HIDEPOSATION m_hp;

signals:

};

#endif // HIDEWINDOW_H
