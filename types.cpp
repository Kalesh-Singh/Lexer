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

void StateList::add(Thread thread) {
    if (thread.inst.listType != listType) {
        thread.inst.listType = listType;
        threads.push_back(thread);
    }
}

Thread StateList::remove() {
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

unsigned long StateList::size() {
    return threads.size();
}

const Thread &StateList::operator[](unsigned long i) {
    return threads[i];
}
