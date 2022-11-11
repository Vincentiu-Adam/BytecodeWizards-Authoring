#ifndef BASEINSTRUCTIONWIDGET_H
#define BASEINSTRUCTIONWIDGET_H

#include "Iauthoringwidget.h"

class BaseInstructionWidget : public IAuthoringWidget
{
public:
    BaseInstructionWidget(const QPoint& startPosition, const QString& instructionTitle);

    virtual void Draw(QPainter& painter) override;

private:
    const int WIDTH                 = 120;
    const int HEIGHT                = 60;
    const int BORDER_WIDTH          = 1;
    const int CORNER_RADIUS_X       = 5;
    const int CORNER_RADIUS_Y       = 5;
    const int FONT_SIZE             = 10;
    const int TITLE_MARGING_TOP     = 20;
    const int CONNECTOR_SIZE        = 8;
    const int CONNECTOR_MARGIN_X    = 0;
    const int CONNECTOR_MARGIN_Y    = 3;

    QPoint position;

    QString title;

    void DrawEntryConnectorShape(QPainterPath& path, const QPoint& position);
    void DrawExitConnectorShape(QPainterPath& path, const QPoint& position);
};

#endif // BASEINSTRUCTIONWIDGET_H
