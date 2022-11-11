#include "canvaswidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDragMoveEvent>

#include "Widgets/simpleinstruction.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget{parent}
{

}

CanvasWidget::~CanvasWidget()
{
    IAuthoringWidget* currentWidget = rootWidget;
    while (currentWidget != NULL)
    {
        IAuthoringWidget* widgetToDelete = currentWidget;
        currentWidget = currentWidget->next;

        delete widgetToDelete;
    }
}

void CanvasWidget::AddWidget(IAuthoringWidget* instruction)
{
    //if root is null then add to root other add to end?
    if (rootWidget == NULL)
    {
        rootWidget = instruction;
        return;
    }

    IAuthoringWidget* currentWidget = rootWidget, *lastWidget = NULL;
    while (currentWidget != NULL)
    {
        lastWidget = currentWidget;
        currentWidget = currentWidget->next;
    }

    //set as next to lastwidget
    lastWidget->next = instruction;
}

IAuthoringWidget* CanvasWidget::GetRootWidget() const
{
    return rootWidget;
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    qDebug("Paint Event call");

    QPainter painter;
    painter.begin(this);
        QBrush whiteBrush(Qt::white);
        painter.setBackground(whiteBrush);

        painter.fillRect(0, 0, width(), height(), whiteBrush);

        //paint all the widgets
        IAuthoringWidget* currentWidget = rootWidget;
        while (currentWidget != NULL)
        {
            currentWidget->Draw(painter);
            currentWidget = currentWidget->next;
        }

    painter.end();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug("Mouse Pressed");

    QPoint mousePos = event->pos();
    qDebug("At position %d %d", mousePos.x(), mousePos.y());

    //check if we contain some instruction
    IAuthoringWidget* currentWidget = rootWidget;

    bool found = false;
    while (!found && currentWidget != NULL)
    {
        found = currentWidget->Contains(mousePos);
        if (found)
        {
            selectedWidget = currentWidget;

            //set position offset based on mouse offset
            widgetSelectionOffset = mousePos - selectedWidget->GetPosition();
            qDebug("Found widget");
        }

        currentWidget = currentWidget->next;
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //released mouse; release widget
    selectedWidget = NULL;
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    //only gets called when mouse is pressed and held
    qDebug("Mouse moved");

    QPoint mousePos = event->pos();
    qDebug("At position %d %d", mousePos.x(), mousePos.y());

    if (selectedWidget != NULL)
    {
        //set widget position based on offset
        QPoint movePos = mousePos - widgetSelectionOffset;
        selectedWidget->Move(movePos);

        //widget moved repaint
        repaint();
    }
}

void CanvasWidget::onSimpleInstructionClicked()
{
    qDebug("Simple instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    SimpleInstruction* simpleInstruction = new SimpleInstruction(canvasCenter);
    AddWidget(simpleInstruction);

    //repaint widget since we added new geometry
    repaint();
}
