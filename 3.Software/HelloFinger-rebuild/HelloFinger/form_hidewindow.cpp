#include "form_hidewindow.h"
#include "ui_form_hidewindow.h"


Form_HideWindow::Form_HideWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_HideWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->move(0,300);

    QRect rect = QGuiApplication::primaryScreen()->geometry();
    m_screenWidth = rect.width();
    m_screenheight = rect.height();
    qDebug() << "宽度为:" <<m_screenWidth;
    qDebug() << "高度为:" <<m_screenheight;

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowOpacity(0.5);      //设置透明度

    ui->listWidget_func->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_func->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

bool Form_HideWindow::isWindowInScreen(QPoint pos)
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
void Form_HideWindow::hideWindow()
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
void Form_HideWindow::showWindow()
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

void Form_HideWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isLMousePress = true;
        m_relativePos = event->globalPos() - pos();//记录相对位置
    }
}


void Form_HideWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_isLMousePress = false;
}

void Form_HideWindow::mouseMoveEvent(QMouseEvent *event)
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


void Form_HideWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(m_hp != HP_None)
        showWindow();
}

void Form_HideWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(m_hp != HP_None)
        hideWindow();
}



Form_HideWindow::~Form_HideWindow()
{
    delete ui;
}
