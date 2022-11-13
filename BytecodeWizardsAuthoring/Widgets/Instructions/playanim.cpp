#include "playanim.h"

PlayAnim::PlayAnim(const QPoint& startPosition, QWidget* const parent) : SingleValueWizardInstruction(startPosition, "PLAY_ANIM", parent)
{
    AMOUNT_TEXT = "Anim ID :";
}

void PlayAnim::Generate(QByteArray& bytecode)
{
    bytecode.append(0xC0);

    //set animation value
    int animationValue = GetAmountValue();
    bytecode.append(animationValue);

    //set wizard ID
    bytecode.append(0xC0);

    //append value
    int wizardIDValue = GetValue();
    bytecode.append(wizardIDValue);

    //set add
    bytecode.append(0xC9);
}
