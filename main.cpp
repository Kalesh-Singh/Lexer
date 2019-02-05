// #define DEBUG    // Uncomment this in helper.h and thompson_vm.h for debugging print outs.

#include "helper.h"
#include "thompson_vm.h"

int main(int argc, char **argv) {

    std::string path = argv[1];
    const std::vector<Instruction> prog = getNfaProgram(path);
    std::string inputStr;
    getline(std::cin, inputStr);

    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    return tVm.tokenize();
}