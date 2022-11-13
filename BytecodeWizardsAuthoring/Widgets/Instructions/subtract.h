#ifndef SUBTRACT_H
#define SUBTRACT_H

#include "Widgets/Base/singlevalueinstruction.h"

class Subtract : public SingleValueInstruction
{
public:
    Subtract(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};
#endif // SUBTRACT_H
