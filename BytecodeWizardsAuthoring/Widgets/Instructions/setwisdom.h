#ifndef SETWISDOM_H
#define SETWISDOM_H

#include "Widgets/Base/wizardinstruction.h"

class SetWisdom : public WizardInstruction
{
public:
    SetWisdom(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // SETWISDOM_H
