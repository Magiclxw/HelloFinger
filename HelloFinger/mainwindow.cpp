#include "mainwindow.h"
#include "ui_mainwindow.h"

extern uint8_t TableState[8];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
