//
// Created by kalesh on 2/3/19.
//

#include "types.h"

Instruction::Instruction() = default;

Instruction::Instruction(unsigned int pc, OpCode opCode, char ch, char ch2) :
        pc(pc), opCode(opCode), ch(ch), ch2(ch2) {}

Instruction::Instruction(unsigned int pc, OpCode opCode) :
        pc(pc), opCode(opCode) {}

Instruction::Instruction(unsigned int pc, OpCode opCode, unsigned int xPc) :
        pc(pc), opCode(opCode), xPc(xPc) {}

Instruction::Instruction(unsigned int pc, OpCode opCode, unsigned int xPc, unsigned int yPc) : pc(
        pc), opCode(opCode), xPc(xPc), yPc(yPc) {}

bool Instruction::operator==(const Instruction &rhs) const {

    switch (opCode) {
        case OpCode::CHAR:
            return pc == rhs.pc &&
                   opCode == rhs.opCode &&
                   ch == rhs.ch &&
                   ch2 == rhs.ch2;
        case OpCode::MATCH:
            return pc == rhs.pc &&
                   opCode == rhs.opCode;
        case OpCode::SPLIT:
            return pc == rhs.pc &&
                   opCode == rhs.opCode &&
                   xPc == rhs.xPc &&
                   yPc == rhs.yPc;
        case OpCode::JMP:
            return pc == rhs.pc &&
                   opCode == rhs.opCode &&
                   xPc == rhs.xPc;
    }
}

bool Instruction::operator!=(const Instruction &rhs) const {
    return !(rhs == *this);
}

StateList::StateList(ListType listType) : listType(listType) {}

void StateList::add(Instruction &inst) {
    if (inst.listType != listType) {
        inst.listType = listType;
        insts.push_back(inst);
    }
}

Instruction StateList::pop() {
    Instruction inst = insts.back();
    insts.pop_back();
    return inst;
}

void StateList::clear() {
    insts.clear();
}

void StateList::setListType(ListType listType) {
    this->listType = listType;
}

unsigned long StateList::size() const {
    return insts.size();
}

const Instruction &StateList::operator[](unsigned long i) {
    return insts[i];
}

const bool StateList::empty() {
    return insts.empty();
}

Match::Match(unsigned int matchPc, const std::string &input, unsigned int startSp, unsigned int matchSp) {
    matchStr = input.substr(startSp, matchSp-startSp);
    this->matchPc = matchPc;
}

void replaceEscapedWithSequence(std::string &str) {
    std::size_t found = str.find('\n');
    while (found != std::string::npos) {
        str.replace(found, 1, "\\n");
        found = str.find('\n');
    }
    found = str.find('\t');
    while (found != std::string::npos) {
        str.replace(found, 1, "\\t");
        found = str.find('\t');
    }
}

std::ostream &operator<<(std::ostream &out, const Match &match) {
    replaceEscapedWithSequence(const_cast<Match&>(match).matchStr);
    out << match.matchPc << ":\"" << match.matchStr << "\"";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Instruction &inst) {
    switch (inst.opCode) {
        case OpCode::CHAR:
            out << inst.pc << " CHAR " << (int) inst.ch << " " << (int) inst.ch2 << std::endl;
            return out;
        case OpCode::MATCH:
            out << inst.pc << " MATCH" << std::endl;
            return out;
        case OpCode::JMP:
            out << inst.pc << " JMP " << inst.xPc << std::endl;
            return out;
        case OpCode::SPLIT:
            out << inst.pc << " SPLIT " << inst.xPc << " " << inst.yPc << std::endl;
            return out;
    }
}

std::ostream &operator<<(std::ostream &out, const StateList &list) {
    out << "[";
    for (int i = 0; i < list.size(); i++) {
        if (i != list.size() - 1) {
            out << list.insts[i].pc << ", ";
        } else {
            out << list.insts[i].pc;
        }
    }
    out << "]";
    return out;
}
