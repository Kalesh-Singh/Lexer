//
// Created by kalesh on 2/3/19.
//

#ifndef THOMPSONVM_TYPES_H
#define THOMPSONVM_TYPES_H

#include <vector>

enum class OpCode {
    CHAR,
    MATCH,
    JMP,
    SPLIT
};

enum class ListType {
    CURRENT,
    NEXT,
    NONE
};

class Instruction {
public:
    unsigned int pc;
    OpCode opCode;
    char ch;
    char ch2;
    unsigned int xPc;
    unsigned int yPc;
    ListType listType = ListType::NONE;

    Instruction();                                                                              // Default constructor

    Instruction(unsigned int pc, OpCode opCode, char ch, char ch2);                                  // CHAR constructor
    Instruction(unsigned int pc, OpCode opCode);                                           // MATCH constructor
    Instruction(unsigned int pc, OpCode opCode, unsigned int xPc);                       // JMP constructor
    Instruction(unsigned int pc, OpCode opCode, unsigned int xPc, unsigned int yPc);   // SPLIT constructor
};

class Thread {
public:
    Instruction inst;
    Thread(Instruction &inst) : inst(inst) {}
};

class StateList {
private:
    ListType listType;
    std::vector<Thread> threads;
public:
    StateList(ListType listType);
    void setListType(ListType listType);
    void add(Thread &thread);
    Thread remove();
    void clear();
};

#endif //THOMPSONVM_TYPES_H
