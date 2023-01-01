#ifndef ENROLLSTATE_H
#define ENROLLSTATE_H

#include <QWidget>

namespace Ui {
class enrollstate;
}

class enrollstate : public QWidget
{
    Q_OBJECT

public:
    explicit enrollstate(QWidget *parent = nullptr);
    ~enrollstate();

private:
    Ui::enrollstate *ui;
public slots:
    void SL_InterfaceUpdate(void);

};

#endif // ENROLLSTATE_H
