#include "form_hidewindow.h"
#include "ui_form_hidewindow.h"
#include "system/system_init.h"
#include <QFileInfo>
#include <QFileIconProvider>
#include <QLabel>

Form_HideWindow::Form_HideWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_HideWindow)
{
    ui->setupUi(this);
    //this->setFixedSize(this->width(),this->height());
    this->setFixedSize(40,250);
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

void Form_HideWindow::File_Update_Hidewindow_Content()
{
    uint8_t item = 0;
    uint8_t itemNum = 0;
    ui->listWidget_func->clear();
    itemNum = File_HideWindow_ItemNum_Get();
    while(1)
    {

        if(item == itemNum)
        {
            break;
        }
        QString path = File_HideWindow_Item_Read(item);
        {
            QListWidgetItem *listwidgetitem = new QListWidgetItem;
            QFileInfo fileInfo(path);
            QFileIconProvider iconProvider;
            QIcon icon = iconProvider.icon(fileInfo);
            QLabel label;
            label.setPixmap(icon.pixmap(50,50));
            listwidgetitem->setIcon(icon);
            ui->listWidget_func->addItem(listwidgetitem);

        }
        item++;
    }
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

void Form_HideWindow::Slot_UpdateCheckedItem(int dir)
{
    if(dir == Qt::Key_Left)
    {
        uint8_t currentIndex = ui->listWidget_func->currentIndex().row();
        uint8_t nextIndex = currentIndex+1;

        if(currentIndex == ui->listWidget_func->count()-1)
        {
            nextIndex = 0;
        }
        ui->listWidget_func->setCurrentRow(nextIndex);

    }

    if(dir == Qt::Key_Right)
    {
        uint8_t currentIndex = ui->listWidget_func->currentIndex().row();
        uint8_t nextIndex = currentIndex-1;
        if(currentIndex == 0 )
        {
            nextIndex = ui->listWidget_func->count()-1;
        }
        ui->listWidget_func->setCurrentRow(nextIndex);
    }
}


Form_HideWindow::~Form_HideWindow()
{
    delete ui;
}
