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
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void onGetHealthInstructionClicked();
    void onSetHealthInstructionClicked();
    void onGetWisdomInstructionClicked();
    void onSetWisdomInstructionClicked();
    void onSetLiteralInstructionClicked();
    void onAddInstructionClicked();
    void onSubtractInstructionClicked();
    void onMultiplyInstructionClicked();
    void onDivideInstructionClicked();
    void onPlayAnimInstructionClicked();
    void onPlayVFXInstructionClicked();

private:
    IAuthoringWidget *rootWidget = NULL;

    IAuthoringWidget *selectedWidget = NULL;

    MoveMode moveMode = MoveMode::WIDGET_MOVE;

    QPoint widgetSelectionOffset;

    QList<IAuthoringWidget*> widgets;

    void AddWidget(IAuthoringWidget* instruction);
};

#endif // CANVASWIDGET_H
