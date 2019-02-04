//
// Created by kalesh on 2/3/19.
//

#ifndef THOMPSONVM_THOMPSON_VM_H
#define THOMPSONVM_THOMPSON_VM_H

#include "types.h"
#include <vector>
#include <string>
#include <set>

class ThompsonVm {
private:
    std::vector<Instruction> program;
    std::string input;
    unsigned int pc = 0;
    unsigned int sp = 0;
    StateList currList = StateList(ListType::CURRENT);
    StateList nextList = StateList(ListType::NEXT);

public:
    ThompsonVm(const std::vector<Instruction> &program, const std::string &input);
    void tokenize();
};


#endif //THOMPSONVM_THOMPSON_VM_H
