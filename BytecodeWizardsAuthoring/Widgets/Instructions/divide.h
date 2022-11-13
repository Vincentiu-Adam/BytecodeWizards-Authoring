#ifndef DIVIDE_H
#define DIVIDE_H

#include "Widgets/Base/singlevalueinstruction.h"

class Divide : public SingleValueInstruction
{
public:
    Divide(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // DIVIDE_H
