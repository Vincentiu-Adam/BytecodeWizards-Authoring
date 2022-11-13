#include "gethealth.h"

GetHealth::GetHealth(const QPoint& startPosition, QWidget* const parent) : WizardInstruction(startPosition, "GET_HEALTH", parent)
{

}

void GetHealth::Generate(QByteArray& bytecode)
{
    //set literal instruction first
    bytecode.append(0xC0);

    //append value
    int literalValue = GetValue();
    bytecode.append(literalValue);

    bytecode.append(0xC1);
}
