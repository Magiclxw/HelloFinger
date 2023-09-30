#include "form_enrollstate.h"
#include "ui_form_enrollstate.h"

Form_EnrollState::Form_EnrollState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_EnrollState)
{
    ui->setupUi(this);
}

Form_EnrollState::~Form_EnrollState()
{
    delete ui;
}
