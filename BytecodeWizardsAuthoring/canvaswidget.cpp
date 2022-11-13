#include "canvaswidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDragMoveEvent>

#include "Widgets/Instructions/setliteral.h"
#include "Widgets/Instructions/add.h"
#include "Widgets/Instructions/subtract.h"
#include "Widgets/Instructions/multiply.h"
#include "Widgets/Instructions/divide.h"
#include "Widgets/Instructions/gethealth.h"
#include "Widgets/Instructions/sethealth.h"
#include "Widgets/Instructions/getwisdom.h"
#include "Widgets/Instructions/setwisdom.h"
#include "Widgets/Instructions/playanim.h"
#include "Widgets/Instructions/playvfx.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget{parent}
{
    //accept key events through click focus
    setFocusPolicy(Qt::ClickFocus);
}

CanvasWidget::~CanvasWidget()
{
    IAuthoringWidget* widget;
    foreach (widget, widgets)
    {
        delete widget;
    }

    widgets.clear();
}

void CanvasWidget::AddWidget(IAuthoringWidget* instruction)
{
    //if root is null then add to root other add to end?
    if (rootWidget == NULL)
    {
        rootWidget = instruction;
        rootWidget->SetRoot();
    }

    widgets.append(instruction);
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
        IAuthoringWidget* widget;
        foreach (widget, widgets)
        {
            widget->Draw(painter);
        }

    painter.end();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug("Mouse Pressed");

    QPoint mousePos = event->pos();
    qDebug("At position %d %d", mousePos.x(), mousePos.y());

    //reset selection on mouse press
    selectedWidget = NULL;

    //check if we contain some instruction

    bool found = false;

    int i = 0;
    while (!found && i < widgets.count())
    {
        IAuthoringWidget* currentWidget = widgets[i];

        bool inWidget = currentWidget->Contains(mousePos);
        bool inExitConnector = currentWidget->ContainsExitConnector(mousePos);

        found = inWidget || inExitConnector;
        if (found)
        {
            selectedWidget = currentWidget;

            //check if we didn't click on the exit connector instead
            if (inExitConnector)
            {
                moveMode = MoveMode::CONNECTOR_MOVE;
                qDebug("Found exit connector");

                //create a line that we will move via mouse cursor
                selectedWidget->CreateExitConnectorLine();

                //if we have a next widget then we need to remove the entry connector line and reset the next pointer
                if (selectedWidget->next != NULL)
                {
                    selectedWidget->next->SetEntryConnectorLine(NULL);
                    selectedWidget->next->prev = NULL;
                    selectedWidget->next = NULL;
                }
            }
            else
            {
                //if we did not click on the connector move widget instead
                moveMode = MoveMode::WIDGET_MOVE;
                qDebug("Found widget");

                //set position offset based on mouse offset
                widgetSelectionOffset = mousePos - selectedWidget->GetPosition();
            }
        }

        i++;
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //if in connector move mode, check if we released on another widget exit node and link to that
    if (selectedWidget != NULL && moveMode == MoveMode::CONNECTOR_MOVE)
    {
        QPoint mousePos = event->pos();

        //check if we contain some instruction
        bool found = false;

        int i = 0;
        while (!found && i < widgets.count())
        {
            IAuthoringWidget* currentWidget = widgets[i];
            found = currentWidget != selectedWidget && currentWidget->ContainsEntryConnector(mousePos);
            if (found)
            {
                currentWidget->SetEntryConnectorLine(selectedWidget->GetExitConnectorLine());
                selectedWidget->next = currentWidget;

                //if current widget had an entry already, we need to remove the line for that entry
                if (currentWidget->prev != NULL)
                {
                    currentWidget->prev->SetExitLineEndPos(QPoint(-1,-1));
                    currentWidget->prev->next = NULL;

                    //line deleted repaint
                    repaint();
                }

                currentWidget->prev = selectedWidget;

                //if current widget is root then we change with new root
                if (currentWidget == rootWidget)
                {
                    currentWidget->ResetRoot();

                    rootWidget = selectedWidget;
                    selectedWidget->SetRoot();

                    //root updated repaint
                    repaint();
                }
            }

            i++;
        }

        //if we did not release on any exit node then just remove the line
        if (!found)
        {
            selectedWidget->SetExitLineEndPos(QPoint(-1,-1));

            //line deleted repaint
            repaint();
        }
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    //ignore event if no focus
    if (!hasFocus())
    {
        return;
    }

    //only gets called when mouse is pressed and held
    qDebug("Mouse moved");

    QPoint mousePos = event->pos();
    qDebug("At position %d %d", mousePos.x(), mousePos.y());

    if (selectedWidget != NULL)
    {
        switch (moveMode)
        {
            case MoveMode::WIDGET_MOVE:
            {
                //set widget position based on offset
                QPoint movePos = mousePos - widgetSelectionOffset;
                selectedWidget->Move(movePos);

                break;
            }

            case MoveMode::CONNECTOR_MOVE:
            {
                selectedWidget->SetExitLineEndPos(mousePos);
                break;
            }
        }

        //widget moved repaint
        repaint();
    }
}

void CanvasWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug("Key pressed %d", event->key());
    qDebug("Delete key %d", Qt::Key_Delete);

    if (event->key() != Qt::Key_Delete || selectedWidget == NULL)
    {
        QWidget::keyPressEvent(event);
        return;
    }

    //delete selected widget
    widgets.removeOne(selectedWidget);

    //if root widget; set next or first as root widget or null if next is null
    if (rootWidget == selectedWidget)
    {
        rootWidget = selectedWidget->next;
        if (rootWidget == NULL && widgets.count() > 0)
        {
            rootWidget = widgets[0];
        }

        if (rootWidget != NULL)
        {
            rootWidget->SetRoot();
        }
    }

    delete selectedWidget;

    //widget deleted repaint
    repaint();
}

void CanvasWidget::onGetHealthInstructionClicked()
{
    qDebug("Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    GetHealth* getHealthInstruction = new GetHealth(canvasCenter, this);
    AddWidget(getHealthInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onSetHealthInstructionClicked()
{
    qDebug("Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    SetHealth* setHealthInstruction = new SetHealth(canvasCenter, this);
    AddWidget(setHealthInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onGetWisdomInstructionClicked()
{
    qDebug("Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    GetWisdom* getWisdomInstruction = new GetWisdom(canvasCenter, this);
    AddWidget(getWisdomInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onSetWisdomInstructionClicked()
{
    qDebug("Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    SetWisdom* setWisdomInstruction = new SetWisdom(canvasCenter, this);
    AddWidget(setWisdomInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onSetLiteralInstructionClicked()
{
    qDebug("Single Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    SetLiteral* setLiteralInstruction = new SetLiteral(canvasCenter, this);
    AddWidget(setLiteralInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onAddInstructionClicked()
{
    qDebug("Single Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    Add* addInstruction = new Add(canvasCenter, this);
    AddWidget(addInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onSubtractInstructionClicked()
{
    qDebug("Single Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    Subtract* subtractInstruction = new Subtract(canvasCenter, this);
    AddWidget(subtractInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onMultiplyInstructionClicked()
{
    qDebug("Single Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    Multiply* multiplyInstruction = new Multiply(canvasCenter, this);
    AddWidget(multiplyInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onDivideInstructionClicked()
{
    qDebug("Single Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    Divide* divideInstruction = new Divide(canvasCenter, this);
    AddWidget(divideInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onPlayAnimInstructionClicked()
{
    qDebug("Double Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    PlayAnim* playAnimInstruction = new PlayAnim(canvasCenter, this);
    AddWidget(playAnimInstruction);

    //repaint widget since we added new geometry
    repaint();
}

void CanvasWidget::onPlayVFXInstructionClicked()
{
    qDebug("Double Value instruction here?");

    QPoint canvasCenter(width() * 0.5f, height() * 0.5f);

    PlayVFX* playVFXInstruction = new PlayVFX(canvasCenter, this);
    AddWidget(playVFXInstruction);

    //repaint widget since we added new geometry
    repaint();
}
