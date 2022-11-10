#include "authoringwindow.h"
#include "./ui_authoringwindow.h"

#include <QFile>

AuthoringWindow::AuthoringWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthoringWindow)
{
    ui->setupUi(this);

    canvas = ui->canvas;

    //connect slots
    QObject::connect(ui->simpleInstruction, &QPushButton::clicked, ui->canvas, &CanvasWidget::onSimpleInstructionClicked);
    QObject::connect(ui->setLiteral, &QPushButton::clicked, this, &AuthoringWindow::onGenerate);
}

void AuthoringWindow::Generate(IAuthoringWidget* rootWidget)
{
    //iterate through all widgets and fetch their pointer
    QByteArray bytecode; //find a way to remove the fixed 100 character limit kek

    IAuthoringWidget* currentWidget = rootWidget;
    while (currentWidget != NULL)
    {
        currentWidget->Generate(bytecode);
        currentWidget = currentWidget->next;
    }

    QString filename = "bytecode.bin";
    QFile file(filename);

    if (file.open(QIODevice::ReadWrite))
    {
        file.write(bytecode);
    }
}

void AuthoringWindow::onGenerate()
{
    qDebug("Generating stuff");
    Generate(canvas->GetRootWidget());
}

AuthoringWindow::~AuthoringWindow()
{
    delete ui;
}

