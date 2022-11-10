#include "simpleinstruction.h"

SimpleInstruction::SimpleInstruction()
{

}

void SimpleInstruction::Generate(QByteArray& bytecode)
{
    bytecode.append(0x0A);
}

void SimpleInstruction::Draw()
{

}

SimpleInstruction::~SimpleInstruction()
{

}
