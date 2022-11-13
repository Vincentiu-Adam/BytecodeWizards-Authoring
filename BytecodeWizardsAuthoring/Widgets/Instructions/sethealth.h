#ifndef SETHEALTH_H
#define SETHEALTH_H

#include "Widgets/Base/wizardinstruction.h"

class SetHealth : public WizardInstruction
{
public:
    SetHealth(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // SETHEALTH_H
