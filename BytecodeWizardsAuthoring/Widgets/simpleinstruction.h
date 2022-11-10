#ifndef SIMPLEINSTRUCTION_H
#define SIMPLEINSTRUCTION_H

#include "IAuthoringWidget.h"

#include <QByteArray>

class SimpleInstruction : public IAuthoringWidget
{
public:
    SimpleInstruction();
    ~SimpleInstruction() override;

    void Generate(QByteArray& bytecode) override;

    void Draw() override;
};

#endif // SIMPLEINSTRUCTION_H
