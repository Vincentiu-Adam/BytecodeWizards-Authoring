#include "authoringwindow.h"
#include "./ui_authoringwindow.h"

#include <QFile>
#include <QFileDialog>

AuthoringWindow::AuthoringWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthoringWindow)
{
    ui->setupUi(this);

    canvas = ui->canvas;

    //connect slots
    QObject::connect(ui->getHealth, &QPushButton::clicked, ui->canvas, &CanvasWidget::onGetHealthInstructionClicked);
    QObject::connect(ui->setHealth, &QPushButton::clicked, ui->canvas, &CanvasWidget::onSetHealthInstructionClicked);
    QObject::connect(ui->getWisdom, &QPushButton::clicked, ui->canvas, &CanvasWidget::onGetWisdomInstructionClicked);
    QObject::connect(ui->setWisdom, &QPushButton::clicked, ui->canvas, &CanvasWidget::onSetWisdomInstructionClicked);
    QObject::connect(ui->setLiteral, &QPushButton::clicked, ui->canvas, &CanvasWidget::onSetLiteralInstructionClicked);
    QObject::connect(ui->add, &QPushButton::clicked, ui->canvas, &CanvasWidget::onAddInstructionClicked);
    QObject::connect(ui->subtract, &QPushButton::clicked, ui->canvas, &CanvasWidget::onSubtractInstructionClicked);
    QObject::connect(ui->multiply, &QPushButton::clicked, ui->canvas, &CanvasWidget::onMultiplyInstructionClicked);
    QObject::connect(ui->divide, &QPushButton::clicked, ui->canvas, &CanvasWidget::onDivideInstructionClicked);
    QObject::connect(ui->playAnim, &QPushButton::clicked, ui->canvas, &CanvasWidget::onPlayAnimInstructionClicked);
    QObject::connect(ui->playVFX, &QPushButton::clicked, ui->canvas, &CanvasWidget::onPlayVFXInstructionClicked);
    QObject::connect(ui->generate, &QPushButton::clicked, this, &AuthoringWindow::onGenerate);
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

    QString filename = QFileDialog::getSaveFileName(this, tr("Save Spell"), "", tr("Spell Files (*.bin)"));
    if (filename.isEmpty())
    {
        filename = "bytecode.bin";
    }

    QFile file(filename);

    if (file.open(QIODevice::WriteOnly))
    {
        file.resize(0); //clear existing contents and write again
        file.write(bytecode);
    }

    qDebug("Generate Done");
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

