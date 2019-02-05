// #define DEBUG    // Uncomment to for debug prints

#include "helper.h"
#include "thompson_vm.h"
#include <stdio.h>


int main(int argc, char **argv) {

    // TODO:
    // Read from stdin for input
    // Read the path from the 1st arg
    // return the proper exit code.
#ifdef DEBUG
    std::cout << "NFA File: " << argv[1] << std::endl;
#endif
    std::string path = argv[1];

    const std::vector<Instruction> prog = getNfaProgram(path);

    std::string inputStr;
    getline(std::cin, inputStr);

    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    return tVm.tokenize();
}