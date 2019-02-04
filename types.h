//
// Created by kalesh on 2/3/19.
//

#ifndef THOMPSONVM_TYPES_H
#define THOMPSONVM_TYPES_H

enum class OpCode {
    CHAR,
    MATCH,
    JMP,
    SPLIT
};

class Instruction {
public:
    unsigned int instNum;
    OpCode opCode;
    char ch;
    unsigned int instX;
    unsigned int instY;

    Instruction();                                                                              // Default constructor

    Instruction(unsigned int instNum, OpCode opCode, char ch);                                  // CHAR constructor
    Instruction(unsigned int instNum, OpCode opCode);                                           // MATCH constructor
    Instruction(unsigned int instNum, OpCode opCode, unsigned int instX);                       // JMP constructor
    Instruction(unsigned int instNum, OpCode opCode, unsigned int instX, unsigned int instY);   // SPLIT constructor
};

#endif //THOMPSONVM_TYPES_H
