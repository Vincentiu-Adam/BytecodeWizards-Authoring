#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>

#include "Widgets/IAuthoringWidget.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

    IAuthoringWidget* GetRootWidget() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void onSimpleInstructionClicked();

private:
    IAuthoringWidget *rootWidget = NULL;

    void AddWidget(IAuthoringWidget* instruction);
};

#endif // CANVASWIDGET_H
