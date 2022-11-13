#ifndef ADD_H
#define ADD_H

#include "Widgets/Base/singlevalueinstruction.h"

class Add : public SingleValueInstruction
{
public:
    Add(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // ADD_H
