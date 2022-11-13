#include "baseinstructionwidget.h"

#include <QPainter>
#include <QPainterPath>

typedef QPainter::RenderHints QRenderHints;

BaseInstructionWidget::BaseInstructionWidget(const QPoint& startPosition, const QString& instructionTitle)
{
    position = startPosition;

    title = instructionTitle;
}

BaseInstructionWidget::~BaseInstructionWidget()
{
    delete exitLine;
    exitLine = NULL;
    entryLine = NULL;

    //if we have a prev widget, set their exit line to null
    if (prev != NULL)
    {
        prev->SetExitLineEndPos(QPoint(-1,-1));
        prev->next = NULL;
    }

    //if we have a next widget, set their entry line to null
    if (next != NULL)
    {
        next->SetEntryConnectorLine(NULL);
        next->prev = NULL;
    }

    prev = NULL;
    next = NULL;
}

bool BaseInstructionWidget::Contains(const QPoint& pos)
{
    //simple check inside rect bounds, no rotation shenanigans
    if (pos.x() < position.x() || pos.x() > position.x() + WIDTH || pos.y() < position.y() || pos.y() > position.y() + HEIGHT)
    {
        return false;
    }

    return true;
}

bool BaseInstructionWidget::ContainsEntryConnector(const QPoint& pos)
{
    QPoint entryConnectorPosition = position + QPoint(CONNECTOR_MARGIN_X + CONNECTOR_SIZE * 0.5, CONNECTOR_MARGIN_Y + HEIGHT * 0.5);

    //simple check inside rect bounds, no rotation shenanigans
    if (pos.x() < entryConnectorPosition.x() - CONNECTOR_SIZE * 1.25 || pos.x() > entryConnectorPosition.x() + CONNECTOR_SIZE * 0.25 || pos.y() < entryConnectorPosition.y() - CONNECTOR_SIZE || pos.y() > entryConnectorPosition.y() + CONNECTOR_SIZE)
    {
        return false;
    }

    return true;
}

bool BaseInstructionWidget::ContainsExitConnector(const QPoint& pos)
{
    QPoint exitConnectorPosition = position + QPoint(CONNECTOR_SIZE * 0.5 + WIDTH - CONNECTOR_MARGIN_X, CONNECTOR_MARGIN_Y + HEIGHT * 0.5);

    //simple check inside rect bounds, no rotation shenanigans
    if (pos.x() < exitConnectorPosition.x() - CONNECTOR_SIZE * 1.25 || pos.x() > exitConnectorPosition.x() + CONNECTOR_SIZE * 0.25 + CONNECTOR_SIZE || pos.y() < exitConnectorPosition.y() - CONNECTOR_SIZE || pos.y() > exitConnectorPosition.y() + CONNECTOR_SIZE)
    {
        return false;
    }

    return true;
}

void BaseInstructionWidget::CreateExitConnectorLine()
{
    //remove previous line if exists and create a new one
    SetExitLineEndPos(QPoint(-1,-1));

    QPoint exitConnectorPosition = position + QPoint(CONNECTOR_SIZE * 0.5 + WIDTH - CONNECTOR_MARGIN_X, CONNECTOR_MARGIN_Y + HEIGHT * 0.5);
    exitLine = new LineSegment(exitConnectorPosition);
}

void BaseInstructionWidget::SetEntryConnectorLine(LineSegment* const lineSegment)
{
    entryLine = lineSegment;

    if (entryLine != NULL)
    {
        //snap to entry point position
        QPoint connectorPosition = position + QPoint(CONNECTOR_MARGIN_X + CONNECTOR_SIZE * 0.5, CONNECTOR_MARGIN_Y + HEIGHT * 0.5);
        entryLine->SetEndPoint(connectorPosition);
    }
}

void BaseInstructionWidget::Move(const QPoint& newPos)
{
    position = newPos;

    //widget moved we need to update line pos as well
    QPoint connectorPosition;
    if (entryLine != NULL)
    {
        connectorPosition = position + QPoint(CONNECTOR_MARGIN_X + CONNECTOR_SIZE * 0.5, CONNECTOR_MARGIN_Y + HEIGHT * 0.5);
        entryLine->SetEndPoint(connectorPosition);
    }

    if (exitLine != NULL)
    {
        connectorPosition = position + QPoint(CONNECTOR_SIZE * 0.5 + WIDTH - CONNECTOR_MARGIN_X, CONNECTOR_MARGIN_Y + HEIGHT * 0.5);
        exitLine->SetStartPoint(connectorPosition);
    }
}

void BaseInstructionWidget::SetExitLineEndPos(const QPoint& endPos)
{
    //clear line if end pos is negative
    if (endPos.x() == -1)
    {
        delete exitLine;
        exitLine = NULL;

        return;
    }

    exitLine->SetEndPoint(endPos);
}

void BaseInstructionWidget::Draw(QPainter& painter, int drawOrder)
{
    //use painter to draw a rect at pos
    QColor cyanTransparent = Qt::cyan;
    cyanTransparent.setAlphaF(0.5f);

    QBrush blueRoundedBrush(cyanTransparent);

    QRenderHints previousHints = painter.renderHints();

    //draw rounded rect with AA
    painter.setRenderHint(QPainter::Antialiasing);

    //draw lines first in draw order 0
    switch(drawOrder)
    {
        case 0:
        {
            //draw exit line if exists
            if (exitLine != NULL)
            {
                exitLine->Draw(painter);
            }

            break;
        }

        case 1:
        {
            //create a path for the rounded rect
            QPainterPath roundedRectPath;
            QPoint rectPosition(position.x(), position.y());
            roundedRectPath.addRoundedRect(rectPosition.x(), rectPosition.y(), WIDTH, HEIGHT, CORNER_RADIUS_X, CORNER_RADIUS_Y);

            QPen blackBorderPen(Qt::black, BORDER_WIDTH);
            painter.setPen(blackBorderPen);

            painter.fillPath(roundedRectPath, blueRoundedBrush);
            painter.drawPath(roundedRectPath);

            //draw instruction title
            QFont sizedFont = painter.font();
            sizedFont.setPointSize(FONT_SIZE);
            sizedFont.setBold(isRoot);

            painter.setFont(sizedFont);

            QFontMetrics fontMetrics(sizedFont);

            QPoint textPosition(position.x(), position.y());
            float textWidth = fontMetrics.size(Qt::TextSingleLine, title).width();

            textPosition += QPoint((WIDTH - textWidth) * 0.5f , TITLE_MARGING_TOP); //offset text
            painter.drawText(textPosition, title);

            //draw connectors
            roundedRectPath.clear();

            //make sure to reset pen since draw line might ovewrite
            painter.setPen(blackBorderPen);

            rectPosition += QPoint(CONNECTOR_MARGIN_X + CONNECTOR_SIZE * 0.5, CONNECTOR_MARGIN_Y + HEIGHT * 0.5); //left connector
            DrawEntryConnectorShape(roundedRectPath, rectPosition);

            //draw entry red
            blueRoundedBrush.setColor(Qt::red);

            painter.fillPath(roundedRectPath, blueRoundedBrush);
            painter.drawPath(roundedRectPath);

            roundedRectPath.clear();

            rectPosition += QPoint(WIDTH - CONNECTOR_MARGIN_X * 2, 0); //right connector
            DrawExitConnectorShape(roundedRectPath, rectPosition);

            blueRoundedBrush.setColor(Qt::gray);

            painter.fillPath(roundedRectPath, blueRoundedBrush);
            painter.drawPath(roundedRectPath);

            break;
        }
    }

    //restore original hints
    painter.setRenderHints(previousHints);
}

void BaseInstructionWidget::DrawEntryConnectorShape(QPainterPath& path, const QPoint& position)
{
    QPointF connectorP1 = position + QPointF(CONNECTOR_SIZE * 0.25, -CONNECTOR_SIZE);
    QPointF connectorP2 = position + QPointF(-CONNECTOR_SIZE * 1.25, -CONNECTOR_SIZE);
    QPointF connectorP3 = position + QPointF(-CONNECTOR_SIZE * 1.25, CONNECTOR_SIZE);
    QPointF connectorP4 = position + QPointF(CONNECTOR_SIZE * 0.25, CONNECTOR_SIZE);

    QPolygonF connectorShape;
    connectorShape << connectorP1 << connectorP2 << connectorP3 << connectorP4 << connectorP1;

    path.addPolygon(connectorShape);
}

void BaseInstructionWidget::DrawExitConnectorShape(QPainterPath& path, const QPoint& position)
{
    QPointF connectorP1 = position + QPointF(0, -CONNECTOR_SIZE);
    QPointF connectorP2 = position + QPointF(-CONNECTOR_SIZE * 1.25, -CONNECTOR_SIZE);
    QPointF connectorP3 = position + QPointF(-CONNECTOR_SIZE * 1.25, CONNECTOR_SIZE);
    QPointF connectorP4 = position + QPointF(0, CONNECTOR_SIZE);

    QPoint connectorTip = position + QPoint(CONNECTOR_SIZE, 0);

    QPolygonF connectorShape;
    connectorShape << connectorP1 << connectorP2 << connectorP3 << connectorP4 << connectorTip << connectorP1;

    path.addPolygon(connectorShape);
}
