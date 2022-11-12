#ifndef AUTHORINGWINDOW_H
#define AUTHORINGWINDOW_H

#include <QMainWindow>

#include "canvaswidget.h"
#include "Widgets/Base/Iauthoringwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AuthoringWindow; }
QT_END_NAMESPACE

class AuthoringWindow : public QMainWindow
{
    Q_OBJECT

public:
    AuthoringWindow(QWidget *parent = nullptr);
    ~AuthoringWindow();

    void Generate(IAuthoringWidget* rootWidget);

public slots:
    void onGenerate();

private:
    Ui::AuthoringWindow *ui;

    CanvasWidget* canvas;
};
#endif // AUTHORINGWINDOW_H
