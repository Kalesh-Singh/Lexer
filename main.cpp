#include <iostream>
#include "helper.h"
#include "thompson_vm.h"

int main() {
    std::string inputStr;
    getline(std::cin, inputStr);
    std::string path = "nfa.ns";
    const std::vector<Instruction> prog = getNfaProgram(path);
    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    tVm.tokenize();
}