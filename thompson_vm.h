//
// Created by kalesh on 2/3/19.
//

// #define DEBUG   // Uncomment for debugging print outs

#ifndef THOMPSONVM_THOMPSON_VM_H
#define THOMPSONVM_THOMPSON_VM_H

#include "types.h"
#include <set>

class ThompsonVm {
private:
    std::vector<Instruction> program;
    std::string input;
    StateList currList = StateList(ListType::CURRENT);
    StateList nextList = StateList(ListType::NEXT);

public:
    ThompsonVm(const std::vector<Instruction> &program, std::string &input);
    int tokenize();
};

#endif //THOMPSONVM_THOMPSON_VM_H
