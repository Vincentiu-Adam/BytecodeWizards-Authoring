#ifndef BASEINSTRUCTIONWIDGET_H
#define BASEINSTRUCTIONWIDGET_H

#include "Iauthoringwidget.h"
#include "Misc/linesegment.h"

class BaseInstructionWidget : public IAuthoringWidget
{
public:
    BaseInstructionWidget(const QPoint& startPosition, const QString& instructionTitle);
    ~BaseInstructionWidget();

    virtual void Draw(QPainter& painter) override;

    bool Contains(const QPoint& pos) override;
    bool ContainsEntryConnector(const QPoint& pos) override;
    bool ContainsExitConnector(const QPoint& pos) override;

    void CreateExitConnectorLine() override;
    void SetEntryConnectorLine(LineSegment* const lineSegment) override;

    inline LineSegment* GetExitConnectorLine() const override { return exitLine; };

    void Move(const QPoint& newPos) override;

    void SetExitLineEndPos(const QPoint& endPos) override;

    void SetRoot() override { isRoot = true; };

    inline QPoint GetPosition() const override { return position; };

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

    bool isRoot = false;

    QPoint position;

    QString title;

    LineSegment* entryLine = NULL;
    LineSegment* exitLine = NULL;

    void DrawEntryConnectorShape(QPainterPath& path, const QPoint& position);
    void DrawExitConnectorShape(QPainterPath& path, const QPoint& position);
};

#endif // BASEINSTRUCTIONWIDGET_H
