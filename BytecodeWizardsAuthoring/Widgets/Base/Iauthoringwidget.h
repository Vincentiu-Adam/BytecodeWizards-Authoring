#ifndef IAUTHORINGWIDGET_H
#define IAUTHORINGWIDGET_H

#include "Misc/linesegment.h"

#include <cstddef>
#include <QByteArray>
#include <QPainter>

class IAuthoringWidget
{
public:
    IAuthoringWidget* prev = NULL;
    IAuthoringWidget* next = NULL;

    virtual void Draw(QPainter& painter) = 0;
    virtual void Generate(QByteArray& bytecode) = 0;

    virtual bool Contains(const QPoint& pos) = 0;
    virtual bool ContainsEntryConnector(const QPoint& pos) = 0;
    virtual bool ContainsExitConnector(const QPoint& pos) = 0;

    virtual void Move(const QPoint& newPos) = 0;

    virtual void CreateExitConnectorLine() = 0;
    virtual void SetEntryConnectorLine(LineSegment* const lineSegment) = 0;

    virtual LineSegment* GetExitConnectorLine() const = 0;

    virtual void SetRoot() = 0;
    virtual void ResetRoot() = 0;

    virtual QPoint GetPosition() const = 0;

    virtual void SetExitLineEndPos(const QPoint& endPos) = 0;

    virtual ~IAuthoringWidget() {};
};

#endif // IAUTHORINGWIDGET_H
