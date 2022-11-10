#ifndef IAUTHORINGWIDGET_H
#define IAUTHORINGWIDGET_H

#include <cstddef>
#include <QByteArray>

class IAuthoringWidget
{
public:
    IAuthoringWidget* next = NULL;

    virtual void Draw() = 0;
    virtual void Generate(QByteArray& bytecode) = 0;

    virtual ~IAuthoringWidget() {};
};

#endif // IAUTHORINGWIDGET_H
