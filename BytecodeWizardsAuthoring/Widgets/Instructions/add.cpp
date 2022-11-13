#include "add.h"

Add::Add(const QPoint& startPosition, QWidget* const parent) : SingleValueInstruction(startPosition, "ADD", parent)
{

}

void Add::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    //set add
    bytecode.append(0xC5);
}
