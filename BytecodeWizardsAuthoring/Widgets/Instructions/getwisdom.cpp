#include "getwisdom.h"

GetWisdom::GetWisdom(const QPoint& startPosition, QWidget* const parent) : WizardInstruction(startPosition, "GET_WISDOM", parent)
{

}

void GetWisdom::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    bytecode.append(0xC3);
}
