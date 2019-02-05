//
// Created by kalesh on 2/3/19.
//

#include "types.h"

Instruction::Instruction() {}

Instruction::Instruction(unsigned int pc, OpCode opCode, char ch, char ch2) :
    pc(pc), opCode(opCode), ch(ch), ch2(ch2) {}

Instruction::Instruction(unsigned int pc, OpCode opCode) :
    pc(pc), opCode(opCode) {}

Instruction::Instruction(unsigned int pc, OpCode opCode, unsigned int xPc) :
    pc(pc), opCode(opCode), xPc(xPc) {}

Instruction::Instruction(unsigned int pc, OpCode opCode, unsigned int xPc, unsigned int yPc) : pc(
        pc), opCode(opCode), xPc(xPc), yPc(yPc) {}

StateList::StateList(ListType listType) : listType(listType) {}

void StateList::add(Thread &thread) {
    if (thread.inst.listType != listType) {
        thread.inst.listType = listType;
        threads.push_back(thread);
    }
}

Thread StateList::pop() {
    Thread thread = threads.back();
    threads.pop_back();
    return thread;
}

void StateList::clear() {
    threads.clear();
}

void StateList::setListType(ListType listType) {
    this->listType = listType;
}

unsigned long StateList::size() const {
    return threads.size();
}

const Thread &StateList::operator[](unsigned long i) {
    return threads[i];
}

const bool StateList::empty() {
    return threads.empty();
}

Match::Match(unsigned int matchPc, const std::string &input, unsigned int startSp, unsigned int matchSp) {
    matchStr = input.substr(startSp, matchSp-startSp);
    this->matchPc = matchPc;
}

std::ostream &operator<<(std::ostream &out, const Match &match) {
    out << match.matchPc << ": \"" << match.matchStr << "\"";
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
            out << list.threads[i].inst.pc << ", ";
        } else {
            out << list.threads[i].inst.pc;
        }
    }
    out << "]";
    return out;
}
