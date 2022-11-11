#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QPoint>
#include <QPainter>

class LineSegment
{
public:
    LineSegment(const QPoint& endPos);
    ~LineSegment();

    void Draw(QPainter& painter);

    inline void SetStartPoint(const QPoint& startPos) { start = startPos; };
    inline void SetEndPoint(const QPoint& endPos) { end = endPos; };

    QPointF CalculateCubicBezierPoint(float t, QPointF p0, QPointF p1, QPointF p2, QPointF p3);

private:
    const int LINE_WIDTH            = 3;
    const int CURVE_SEGMENT_COUNT   = 50;
    const float CONTROL_OFFSET      = 100.f;

    QPoint start;
    QPoint end;
};

#endif // LINESEGMENT_H
