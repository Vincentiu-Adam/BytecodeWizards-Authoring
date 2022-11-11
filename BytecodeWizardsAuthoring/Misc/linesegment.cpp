#include "linesegment.h"

#include <QPainterPath>

LineSegment::LineSegment(const QPoint& endPos)
{
    start = endPos;
    end = endPos;
}

LineSegment::~LineSegment()
{

}

void LineSegment::Draw(QPainter& painter)
{
    QPen blackBorderPen(Qt::black, LINE_WIDTH);
    painter.setPen(blackBorderPen);

    //draw some bezier curve with aligned control points
    QPainterPath path;

    QPolygonF curvePolygon;

    //add points along a curve for the polygon (can be done using cubicTo as well, but wanted to see the math behind it...)
    QPointF controlPoint1 = start + QPointF(CONTROL_OFFSET, 0), controlPoint2 = end - QPointF(CONTROL_OFFSET, 0);
    for (int i = 0; i <= CURVE_SEGMENT_COUNT; i++)
    {
        float t = i / (float) CURVE_SEGMENT_COUNT;

        QPointF curvePoint = CalculateCubicBezierPoint(t, start, controlPoint1, controlPoint2, end);
        curvePolygon << curvePoint;
    }

    path.addPolygon(curvePolygon);
    painter.drawPath(path);
}

QPointF LineSegment::CalculateCubicBezierPoint(float t, QPointF p0, QPointF p1, QPointF p2, QPointF p3)
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    QPointF p = uuu * p0;
    p += 3 * uu * t * p1;
    p += 3 * u * tt * p2;
    p += ttt * p3;

    return p;
}
