#ifndef PLAYANIM_H
#define PLAYANIM_H

#include "Widgets/Base/singlevaluewizardinstruction.h"

class PlayAnim : public SingleValueWizardInstruction
{
public:
    PlayAnim(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // PLAYANIM_H
