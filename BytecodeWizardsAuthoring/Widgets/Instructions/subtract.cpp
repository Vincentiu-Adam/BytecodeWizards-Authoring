#include "subtract.h"

Subtract::Subtract(const QPoint& startPosition, QWidget* const parent) : SingleValueInstruction(startPosition, "SUBTRACT", parent)
{

}

void Subtract::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    //set add
    bytecode.append(0xC6);
}
