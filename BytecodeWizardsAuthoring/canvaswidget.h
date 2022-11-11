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
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void onSimpleInstructionClicked();

private:
    IAuthoringWidget *rootWidget = NULL;

    IAuthoringWidget *selectedWidget = NULL;

    QPoint widgetSelectionOffset;

    void AddWidget(IAuthoringWidget* instruction);
};

#endif // CANVASWIDGET_H
