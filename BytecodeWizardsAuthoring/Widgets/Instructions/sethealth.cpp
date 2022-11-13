#include "sethealth.h"

SetHealth::SetHealth(const QPoint& startPosition, QWidget* const parent) : WizardInstruction(startPosition, "SET_HEALTH", parent)
{

}

void SetHealth::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    bytecode.append(0xC2);
}
