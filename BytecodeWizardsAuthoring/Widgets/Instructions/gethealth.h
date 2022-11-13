#ifndef GETHEALTH_H
#define GETHEALTH_H

#include "Widgets/Base/wizardinstruction.h"

class GetHealth : public WizardInstruction
{
public:
    GetHealth(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // GETHEALTH_H
