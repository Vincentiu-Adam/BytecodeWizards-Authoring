#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "Widgets/Base/singlevalueinstruction.h"

class Multiply : public SingleValueInstruction
{
public:
    Multiply(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // MULTIPLY_H
