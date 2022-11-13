#include "divide.h"

Divide::Divide(const QPoint& startPosition, QWidget* const parent) : SingleValueInstruction(startPosition, "DIVIDE", parent)
{

}

void Divide::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    //set add
    bytecode.append(0xC8);
}
