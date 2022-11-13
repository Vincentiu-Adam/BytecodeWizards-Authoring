#include "setliteral.h"

SetLiteral::SetLiteral(const QPoint& startPosition, QWidget* const parent) : SingleValueInstruction(startPosition, "SET_LITERAL", parent)
{

}

void SetLiteral::Generate(QByteArray& bytecode)
{
    //set literal instruction
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);
}
