#include "helper.h"
#include "thompson_vm.h"
#include <stdio.h>

int main(int argc, char **argv) {

    // TODO:
    // Read from stdin for input
    // Read the path from the 1st arg
    // return the proper exit code.

    std::cout << "NFA File: " << argv[1] << std::endl;
    std::string path = argv[1];

    const std::vector<Instruction> prog = getNfaProgram(path);

    char charA = 'a';

    printf("%d\n", charA);


    std::string inputStr;
    // getline(std::cin, inputStr);
    inputStr = "aaa";

    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    return tVm.tokenize();
}