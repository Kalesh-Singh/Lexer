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

class FileNotFound : public std::exception {
public:
    explicit FileNotFound() = default;

    explicit FileNotFound(std::string msg)
            : msg(std::move(msg)) {}

    const char *what() {
        return (!msg.empty()) ? msg.c_str() : nullptr;
    }

private:
    const std::string msg = "";
};

class InvalidOpCode : public std::exception {
public:
    explicit InvalidOpCode() = default;

    explicit InvalidOpCode(std::string msg)
            : msg(std::move(msg)) {}

    const char *what() {
        return (!msg.empty()) ? msg.c_str() : nullptr;
    }

private:
    const std::string msg = "";
};

class MalformedInstruction : public std::exception {
public:
    explicit MalformedInstruction() = default;

    explicit MalformedInstruction(std::string msg)
            : msg(std::move(msg)) {}

    const char *what() {
        return (!msg.empty()) ? msg.c_str() : nullptr;
    }

private:
    const std::string msg = "";
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

    Instruction();                                                                      // Default constructor
    Instruction(unsigned int pc, OpCode opCode, char ch, char ch2);                     // CHAR constructor
    Instruction(unsigned int pc, OpCode opCode);                                        // MATCH constructor
    Instruction(unsigned int pc, OpCode opCode, unsigned int xPc);                      // JMP constructor
    Instruction(unsigned int pc, OpCode opCode, unsigned int xPc, unsigned int yPc);    // SPLIT constructor

    bool operator==(const Instruction &rhs) const;

    bool operator!=(const Instruction &rhs) const;


};

std::ostream &operator<<(std::ostream &out, const Instruction &inst);

class StateList {
public:
    ListType listType;
    std::vector<Instruction> insts;

    explicit StateList(ListType listType);
    void setListType(ListType listType);
    void add(Instruction &inst);
    Instruction pop();
    void clear();
    unsigned long size() const;
    const Instruction& operator[](unsigned long i);
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
