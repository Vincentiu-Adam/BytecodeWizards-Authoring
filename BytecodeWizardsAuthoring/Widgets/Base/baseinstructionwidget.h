#ifndef BASEINSTRUCTIONWIDGET_H
#define BASEINSTRUCTIONWIDGET_H

#include "Iauthoringwidget.h"
#include "Misc/linesegment.h"

class BaseInstructionWidget : public IAuthoringWidget
{

public:
    BaseInstructionWidget(const QPoint& startPosition, const QString& instructionTitle);
    ~BaseInstructionWidget();

    virtual void Draw(QPainter& painter, int drawOrder) override;

    bool Contains(const QPoint& pos) override;
    bool ContainsEntryConnector(const QPoint& pos) override;
    bool ContainsExitConnector(const QPoint& pos) override;

    void CreateExitConnectorLine() override;
    void SetEntryConnectorLine(LineSegment* const lineSegment) override;

    inline LineSegment* GetExitConnectorLine() const override { return exitLine; };

    void Move(const QPoint& newPos) override;

    void SetExitLineEndPos(const QPoint& endPos) override;

    inline void SetRoot() override { isRoot = true; };
    inline void ResetRoot() override { isRoot = false; };

    inline void Select() override { isSelected = true; };
    inline void Deselect() override { isSelected = false; };

    inline QPoint GetPosition() const override { return position; };

protected:
    QPoint position;

    int HEIGHT              = 60;
    int TITLE_MARGING_TOP   = 20;

private:
    const int WIDTH                 = 120;
    const int BORDER_WIDTH          = 1;
    const int CORNER_RADIUS_X       = 5;
    const int CORNER_RADIUS_Y       = 5;
    const int FONT_SIZE             = 10;
    const int CONNECTOR_SIZE        = 8;
    const int CONNECTOR_MARGIN_X    = 0;
    const int CONNECTOR_MARGIN_Y    = 3;

    bool isRoot     = false;
    bool isSelected = false;

    QString title;

    LineSegment* entryLine = NULL;
    LineSegment* exitLine = NULL;

    void DrawEntryConnectorShape(QPainterPath& path, const QPoint& position);
    void DrawExitConnectorShape(QPainterPath& path, const QPoint& position);
};

#endif // BASEINSTRUCTIONWIDGET_H
