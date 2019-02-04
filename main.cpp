#include <iostream>
#include "helper.h"
#include "thompson_vm.h"

int main(int argc, char **argv) {

    // TODO:
    // Read from stdin for input
    // Read the path from the 1st arg
    // return the proper exit code.

    std::string inputStr;
    getline(std::cin, inputStr);
    std::string path = argv[1];
    const std::vector<Instruction> prog = getNfaProgram(path);
    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    tVm.tokenize();
}