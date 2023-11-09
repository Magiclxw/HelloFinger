#ifndef FORM_ENTRANCE_H
#define FORM_ENTRANCE_H

#include <QWidget>

namespace Ui {
class Form_Entrance;
}

class Form_Entrance : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Entrance(QWidget *parent = nullptr);
    ~Form_Entrance();

private:
    Ui::Form_Entrance *ui;
private slots:
    void onDeviceIn(QString VID, QString PID);
    void onDeviceOut(QString VID, QString PID);
};

#endif // FORM_ENTRANCE_H
