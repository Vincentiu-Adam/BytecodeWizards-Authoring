#include "authoringwindow.h"
#include "./ui_authoringwindow.h"

AuthoringWindow::AuthoringWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthoringWindow)
{
    ui->setupUi(this);
}

AuthoringWindow::~AuthoringWindow()
{
    delete ui;
}

