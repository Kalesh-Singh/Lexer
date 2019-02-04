//
// Created by kalesh on 2/3/19.
//

#include "thompson_vm.h"

ThompsonVm::ThompsonVm(const std::vector <Instruction> &program, const std::string &input) :
    program(program), input(input) {}

void ThompsonVm::tokenize() {
    currList.add(Thread(program[pc]));
    for (char &c : input) {
        for (unsigned long i = 0; i < currList.size(); i++) {
            pc = currList[]
        }
    }
}
