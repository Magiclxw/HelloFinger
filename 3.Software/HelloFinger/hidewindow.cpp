#include "hidewindow.h"
#include "ui_hidewindow.h"
#include <QRect>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QtWinExtras>

HideWindow::HideWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HideWindow),
    m_screenWidth(500),
    m_screenheight(500),
    m_isLMousePress(false),
    m_relativePos(0,0)
{
    ui->setupUi(this);

    QRect rect = QGuiApplication::primaryScreen()->geometry();
    m_screenWidth = rect.width();
    m_screenheight=rect.height();
    qDebug() << "宽度为:" <<m_screenWidth;
    qDebug() << "高度为:" <<m_screenheight;

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    resize(50,210);
    move(500,500);

    setWindowOpacity(0.5);      //设置透明度

    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //if(QtWin::isCompositionEnabled()){        //毛玻璃效果
    //    qDebug()<<"可用";
    //    QtWin::extendFrameIntoClientArea(this,-1,-1,-1,-1);
    //    setAttribute(Qt::WA_TranslucentBackground,true);
    //    setAttribute(Qt::WA_NoSystemBackground,false);
    //    setStyleSheet("HideWindow { background: transparent; }");
    //
    //}else{
    //    qDebug()<<"不可用";
    //    QtWin::resetExtendedFrame(this);
    //    setAttribute(Qt::WA_TranslucentBackground,false);
    //    setStyleSheet(QString("HideWindow{background: %1;}").arg(QtWin::realColorizationColor().name()));
    //}


}

//判断当前鼠标位置，并根据位置确定信息
bool HideWindow::isWindowInScreen(QPoint pos)
{
    if(pos.x()<5){
        m_hp = HP_Left;
        return false;
    }
    else if(pos.x()>m_screenWidth-5){
        m_hp = HP_Right;
        return false;
    }
    else if(pos.y()<5){
        m_hp = HP_Top;
        return false;
    }
    else{
        m_hp = HP_None;
        return true;
    }
}


//隐藏窗口的动画
void HideWindow::hideWindow()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setStartValue(QRect(x(),y(),width(),height()));
    if(m_hp == HP_Top)
        animation->setEndValue(QRect(x(),2-height(),width(),height()));
    else if(m_hp == HP_Left)
        animation->setEndValue(QRect(2-width(),y(),width(),height()));
    else if(m_hp == HP_Right)
        animation->setEndValue(QRect(m_screenWidth-2,y(),width(),height()));
    animation->setDuration(250);
    animation->start();
}

//显示窗口的动画
void HideWindow::showWindow()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setStartValue(QRect(x(),y(),width(),height()));
    if(m_hp == HP_Top)
        animation->setEndValue(QRect(x(),0,width(),height()));
    else if(m_hp == HP_Left)
        animation->setEndValue(QRect(0,y(),width(),height()));
    else if(m_hp == HP_Right)
        animation->setEndValue(QRect(m_screenWidth-width(),y(),width(),height()));
    animation->setDuration(250);
    animation->start();
}

void HideWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isLMousePress = true;
        m_relativePos = event->globalPos() - pos();//记录相对位置
    }
}

void HideWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_isLMousePress = false;
}

void HideWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isLMousePress && isWindowInScreen(event->globalPos()))
        move(event->globalPos()-m_relativePos);//实现无边框移动
    else if(m_isLMousePress && !isWindowInScreen(event->globalPos()))
    {
        //特殊位置，移动规则不同
        int x = event->globalPos().x();
        int y = event->globalPos().y();
        if(m_hp == HP_Top)//比如当前鼠标位置为屏幕最上面时，将纵坐标拉至鼠标处，此后只改变横坐标
            move(x-m_relativePos.x(),y);
        else if(m_hp == HP_Left)
            move(x,y-m_relativePos.y());
        else if(m_hp == HP_Right)
            move(x-width(),y-m_relativePos.y());
    }
}

void HideWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(m_hp != HP_None)
        showWindow();
}

void HideWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(m_hp != HP_None)
        hideWindow();
}



HideWindow::~HideWindow()
{
    delete ui;
}
