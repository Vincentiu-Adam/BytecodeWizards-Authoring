#include "playvfx.h"

PlayVFX::PlayVFX(const QPoint& startPosition, QWidget* const parent) : SingleValueWizardInstruction(startPosition, "PLAY_VFX", parent)
{
    AMOUNT_TEXT = "VFX ID :";
}

void PlayVFX::Generate(QByteArray& bytecode)
{
    bytecode.append(0xC0);

    //set animation value
    int vfxValue = GetAmountValue();
    bytecode.append(vfxValue);

    //set wizard ID
    bytecode.append(0xC0);

    //append value
    int wizardIDValue = GetValue();
    bytecode.append(wizardIDValue);

    //set add
    bytecode.append(0xCA);
}
