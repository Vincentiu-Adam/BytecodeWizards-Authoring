#ifndef SIMPLEINSTRUCTION_H
#define SIMPLEINSTRUCTION_H

#include "baseinstructionwidget.h"

#include <QByteArray>

class SimpleInstruction : public BaseInstructionWidget
{
public:
    SimpleInstruction(const QPoint& startPosition, const QString& instructionTitle);

    void Generate(QByteArray& bytecode) override;  
};

#endif // SIMPLEINSTRUCTION_H
