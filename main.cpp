// #define DEBUG    // Uncomment for debugging print outs

#include "helper.h"
#include "thompson_vm.h"

int main(int argc, char **argv) {
#ifdef DEBUG
    std::cout << "NFA File: " << argv[1] << std::endl;
#endif

    // TODO: Print Usage if invalid args

    std::string path = argv[1];
    std::vector<Instruction> prog;
    try {
        prog = getNfaProgram(path);
    } catch (FileNotFound &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    } catch (InvalidOpCode &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    } catch (MalformedInstruction &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }


    std::vector<std::string> lines;
    std::string line;

    while (getline(std::cin, line)) {
        lines.push_back(line);
    }

    std::string inputStr = join(lines, '\n');

    ThompsonVm tVm = ThompsonVm(prog, inputStr);
    return tVm.tokenize();
}