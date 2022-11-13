#include "setwisdom.h"

SetWisdom::SetWisdom(const QPoint& startPosition, QWidget* const parent) : WizardInstruction(startPosition, "SET_WISDOM", parent)
{

}

void SetWisdom::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    bytecode.append(0xC4);
}
