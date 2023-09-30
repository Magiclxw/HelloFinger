#ifndef FORM_ENROLLSTATE_H
#define FORM_ENROLLSTATE_H

#include <QWidget>

namespace Ui {
class Form_EnrollState;
}

class Form_EnrollState : public QWidget
{
    Q_OBJECT

public:
    explicit Form_EnrollState(QWidget *parent = nullptr);
    ~Form_EnrollState();

private:
    Ui::Form_EnrollState *ui;
};

#endif // FORM_ENROLLSTATE_H
