#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Entrance; }
QT_END_NAMESPACE

class Entrance : public QMainWindow
{
    Q_OBJECT

public:
    Entrance(QWidget *parent = nullptr);
    ~Entrance();

private:
    Ui::Entrance *ui;

private slots:
    void onDeviceIn(QString VID, QString PID);
    void onDeviceOut(QString VID, QString PID);
};
#endif // ENTRANCE_H
