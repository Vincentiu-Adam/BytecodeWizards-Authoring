#ifndef SETLITERAL_H
#define SETLITERAL_H

#include "Widgets/Base/singlevalueinstruction.h"

class SetLiteral : public SingleValueInstruction
{
public:
    SetLiteral(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // SETLITERAL_H
