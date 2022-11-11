#include "baseinstructionwidget.h"

#include <QPainter>
#include <QPainterPath>

typedef QPainter::RenderHints QRenderHints;

BaseInstructionWidget::BaseInstructionWidget(const QPoint& startPosition, const QString& instructionTitle)
{
    position = startPosition;

    title = instructionTitle;
}

void BaseInstructionWidget::Draw(QPainter& painter)
{
    //use painter to draw a rect at pos
    QColor cyanTransparent = Qt::cyan;
    cyanTransparent.setAlphaF(0.5f);

    QBrush blueRoundedBrush(cyanTransparent);

    QRenderHints previousHints = painter.renderHints();

    //draw rounded rect with AA
    painter.setRenderHint(QPainter::Antialiasing);

    //create a path for the rounded rect
    QPainterPath roundedRectPath;
    QPoint rectPosition(position.x(), position.y());
    roundedRectPath.addRoundedRect(rectPosition.x(), rectPosition.y(), WIDTH, HEIGHT, CORNER_RADIUS_X, CORNER_RADIUS_Y);

    QPen blackBorderPen(Qt::black, BORDER_WIDTH);
    painter.setPen(blackBorderPen);

    painter.fillPath(roundedRectPath, blueRoundedBrush);
    painter.drawPath(roundedRectPath);

    //draw connectors
    roundedRectPath.clear();

    rectPosition += QPoint(CONNECTOR_MARGIN_X + CONNECTOR_SIZE * 0.5, CONNECTOR_MARGIN_Y + HEIGHT * 0.5); //left connector
    DrawEntryConnectorShape(roundedRectPath, rectPosition);

    rectPosition += QPoint(WIDTH - CONNECTOR_MARGIN_X * 2, 0); //right connector
    DrawExitConnectorShape(roundedRectPath, rectPosition);

    blueRoundedBrush.setColor(Qt::gray);

    painter.fillPath(roundedRectPath, blueRoundedBrush);
    painter.drawPath(roundedRectPath);

    //draw instruction title
    QFont sizedFont = painter.font();
    sizedFont.setPointSize(FONT_SIZE);

    painter.setFont(sizedFont);

    QFontMetrics fontMetrics(sizedFont);

    QPoint textPosition(position.x(), position.y());
    float textWidth = fontMetrics.size(Qt::TextSingleLine, title).width();

    textPosition += QPoint((WIDTH - textWidth) * 0.5f , TITLE_MARGING_TOP); //offset text
    painter.drawText(textPosition, title);

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
