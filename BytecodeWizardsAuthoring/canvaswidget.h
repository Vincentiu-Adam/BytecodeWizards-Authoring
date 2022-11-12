#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>

#include "Widgets/Base/Iauthoringwidget.h"

enum MoveMode { WIDGET_MOVE, CONNECTOR_MOVE };

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

    IAuthoringWidget* GetRootWidget() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void onSimpleInstructionClicked();
    void onValueInstructionClicked();
    void onSingleValueInstructionClicked();
    void onDoubleValueInstructionClicked();

private:
    IAuthoringWidget *rootWidget = NULL;

    IAuthoringWidget *selectedWidget = NULL;

    MoveMode moveMode = MoveMode::WIDGET_MOVE;

    QPoint widgetSelectionOffset;

    QList<IAuthoringWidget*> widgets;

    void AddWidget(IAuthoringWidget* instruction);
};

#endif // CANVASWIDGET_H
