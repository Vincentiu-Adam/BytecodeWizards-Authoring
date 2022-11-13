#include "playanim.h"

PlayAnim::PlayAnim(const QPoint& startPosition, QWidget* const parent) : SingleValueWizardInstruction(startPosition, "PLAY_ANIM", parent)
{

}

void PlayAnim::Generate(QByteArray& bytecode)
{
    //set wizard ID first
    bytecode.append(0xC0);

    //append value
    int wizardIDValue = GetValue();
    bytecode.append(wizardIDValue);

    bytecode.append(0xC0);

    //set animation value
    int animationValue = GetAmountValue();
    bytecode.append(animationValue);

    //set add
    bytecode.append(0xC9);
}
