#ifndef GETWISDOM_H
#define GETWISDOM_H

#include "Widgets/Base/wizardinstruction.h"

class GetWisdom : public WizardInstruction
{
public:
    GetWisdom(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // GETWISDOM_H
