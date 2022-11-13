#ifndef PLAYVFX_H
#define PLAYVFX_H

#include "Widgets/Base/singlevaluewizardinstruction.h"

class PlayVFX : public SingleValueWizardInstruction
{
public:
    PlayVFX(const QPoint& startPosition, QWidget* const parent);

    void Generate(QByteArray& bytecode) override;
};

#endif // PLAYVFX_H
