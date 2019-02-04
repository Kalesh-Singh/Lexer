//
// Created by kalesh on 2/3/19.
//

#include "thompson_vm.h"
#include <iostream>         // TODO: Delete

ThompsonVm::ThompsonVm(const std::vector <Instruction> &program, std::string &input) :
    program(program), input(input) {}

int ThompsonVm::tokenize() {
    int startSp = sp;
    int matchSp = -1;
    int matchPc = -1;

    currList.add(Thread(program[pc]));
    for (char &c : input) {
        for (unsigned long thread = 0; thread < currList.size(); thread++) {
            const Instruction &inst = currList[thread].inst;
            pc = inst.pc;
            switch (inst.opCode) {
                case OpCode::CHAR:
                    if (input[sp] < inst.ch &&  input[sp] > inst.ch2) {
                        break;
                    }
                    nextList.add(Thread(program[pc+1]));
                    break;
                case OpCode::MATCH:
                    return 1;       // FAILED: Not end of string
                case OpCode::JMP:
                    currList.add(Thread(program[inst.xPc]));
                    break;
                case OpCode::SPLIT:
                    currList.add(Thread(program[inst.xPc]));
                    currList.add(Thread(program[inst.yPc]));
                    break;
            }

        }
        // Swap the 2 lists
        currList.setListType(ListType::NEXT);
        nextList.setListType(ListType::CURRENT);
        std::swap(currList, nextList);

        // Clear the next list
        nextList.clear();
    }

    // Get all the matches
    for (int thread = 0; thread < currList.size(); thread++) {
        const Instruction &inst = currList[thread].inst;
        if (inst.opCode == OpCode::MATCH) {
            std::cout << inst.pc << std::endl;
        }
    }
}
