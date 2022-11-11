#ifndef IAUTHORINGWIDGET_H
#define IAUTHORINGWIDGET_H

#include <cstddef>
#include <QByteArray>
#include <QPainter>

class IAuthoringWidget
{
public:
    IAuthoringWidget* next = NULL;

    virtual void Draw(QPainter& painter) = 0;
    virtual void Generate(QByteArray& bytecode) = 0;

    virtual ~IAuthoringWidget() {};
};

#endif // IAUTHORINGWIDGET_H
