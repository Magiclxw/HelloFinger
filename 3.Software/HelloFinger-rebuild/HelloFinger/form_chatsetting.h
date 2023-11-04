#ifndef FORM_CHATSETTING_H
#define FORM_CHATSETTING_H

#include <QDialog>

namespace Ui {
class Form_ChatSetting;
}

class Form_ChatSetting : public QDialog
{
    Q_OBJECT

public:
    explicit Form_ChatSetting(QWidget *parent = nullptr);
    ~Form_ChatSetting();

private slots:
    void on_pushButton_cancel_chat_config_clicked();

private:
    Ui::Form_ChatSetting *ui;
};

#endif // FORM_CHATSETTING_H
