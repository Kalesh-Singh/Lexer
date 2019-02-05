//
// Created by kalesh on 2/3/19.
//

#ifndef THOMPSONVM_TYPES_H
#define THOMPSONVM_TYPES_H

#include <iostream>
#include <vector>
#include <string>

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

std::ostream &operator<<(std::ostream &out, const Instruction &inst);

class Thread {
public:
    Instruction inst;

    explicit Thread(Instruction &inst) : inst(inst) {}
};

class StateList {
public:
    ListType listType;
    std::vector<Thread> threads;

    explicit StateList(ListType listType);
    void setListType(ListType listType);
    void add(Thread &thread);
    Thread pop();
    void clear();
    unsigned long size() const;
    const Thread& operator[](unsigned long i);
    const bool empty();
};

std::ostream &operator<<(std::ostream &out, const StateList &list);

class Match {
public:
    std::string matchStr;
    int matchPc;
    Match(unsigned int matchPc, const std::string &input, unsigned int startSp, unsigned int matchSp);
};

std::ostream &operator<<(std::ostream &out, const Match &match);

#endif //THOMPSONVM_TYPES_H
