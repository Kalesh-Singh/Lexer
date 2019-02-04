//
// Created by kalesh on 2/3/19.
//

#include "types.h"

Instruction::Instruction() {}

Instruction::Instruction(unsigned int instNum, OpCode opCode, char ch) : instNum(instNum), opCode(opCode), ch(ch) {}

Instruction::Instruction(unsigned int instNum, OpCode opCode) : instNum(instNum), opCode(opCode) {}

Instruction::Instruction(unsigned int instNum, OpCode opCode, unsigned int instX) : instNum(instNum), opCode(opCode),
                                                                                    instX(instX) {}

Instruction::Instruction(unsigned int instNum, OpCode opCode, unsigned int instX, unsigned int instY) : instNum(
        instNum), opCode(opCode), instX(instX), instY(instY) {}
