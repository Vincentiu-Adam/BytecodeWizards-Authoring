#include "simpleinstruction.h"

SimpleInstruction::SimpleInstruction(const QPoint& startPosition) : BaseInstructionWidget(startPosition, "GET_HEALTH")
{

}

void SimpleInstruction::Generate(QByteArray& bytecode)
{
    bytecode.append(0x0A);
}

SimpleInstruction::~SimpleInstruction()
{

}
