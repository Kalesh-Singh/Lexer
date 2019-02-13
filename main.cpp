// #define DEBUG    // Uncomment for debugging print outs

#include "helper.h"
#include "thompson_vm.h"

void usage() {
    std::cout << std::endl << "Usage:" << std::endl;
    std::cout << "\t./pr01 [Precompiled NFA program pathname]" << std::endl << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage();
        std::cerr << "Expects the NFA program as the first argument to pr01" << std::endl << std::endl;
        return 1;
    }

#ifdef DEBUG
    std::cout << "NFA File: " << argv[1] << std::endl;
#endif
    std::string path = argv[1];

    const std::vector<Instruction> prog = getNfaProgram(path);


    std::vector<std::string> lines;
    std::string line;

    while (getline(std::cin, line)) {
        lines.push_back(line);
    }

    std::string inputStr = join(lines, '\n');

    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    return tVm.tokenize();
}