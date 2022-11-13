#include "multiply.h"

Multiply::Multiply(const QPoint& startPosition, QWidget* const parent) : SingleValueInstruction(startPosition, "MULTIPLY", parent)
{

}

void Multiply::Generate(QByteArray& bytecode)
{
    if (!IsEmpty())
    {
        //set literal instruction first
        bytecode.append(0xC0);

        //append value
        int literalValue = GetValue();
        bytecode.append(literalValue);
    }

    //set multiply
    bytecode.append(0xC7);
}
