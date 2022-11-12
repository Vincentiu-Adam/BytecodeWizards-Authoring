#include "simpleinstruction.h"

SimpleInstruction::SimpleInstruction(const QPoint& startPosition, const QString& instructionTitle) : BaseInstructionWidget(startPosition, instructionTitle)
{
    HEIGHT = 35;
    TITLE_MARGING_TOP = 24;
}

SimpleInstruction::~SimpleInstruction()
{

}

void SimpleInstruction::Generate(QByteArray& bytecode)
{
    bytecode.append(0x0A);
}

