//
// Created by kalesh on 2/3/19.
//

#include "thompson_vm.h"

ThompsonVm::ThompsonVm(const std::vector<Instruction> &program, std::string &input) :
        program(program), input(input) {}

int ThompsonVm::tokenize() {
    std::vector<Match> matches;

    int startSp = 0;
    int matchSp = -1;
    int matchPc = -1;

    currList.add(program[0]);

    for (unsigned int sp = 0; sp <= input.size(); sp++) {
        while (!currList.empty()) {
            const Instruction inst = currList.pop();
            unsigned int pc = inst.pc;
            if (pc >= program.size()) {
                throw InvalidPC("Program Counter \"" + std::to_string(pc) + "\" out of range");
            }
            program[pc].listType = ListType::NONE;
            switch (inst.opCode) {
                case OpCode::CHAR:
                    if (sp < input.size() && input[sp] >= inst.ch && input[sp] <= inst.ch2) {
                        if (pc + 1 < program.size() - 1) {
                            nextList.add(program[pc + 1]);
                        }
                    }
                    break;
                case OpCode::MATCH:
                    if (matchSp < sp) {         // If the match was shorter than the current match
                        matchPc = pc;
                        matchSp = sp;
                    } else if (matchPc > pc) {  // Choose the match that came earlier
                        matchPc = pc;
                        matchSp = sp;
                    }
#ifdef DEBUG
                    std::cout << "Matched: " << matchPc << ": [" << startSp << ", " << matchSp << ")" << std::endl;
#endif
                    break;
                case OpCode::JMP:
                    if (inst.xPc > program.size() - 1) {
                        throw InvalidPC("Argument to JMP Instruction at PC " + std::to_string(pc) + ", is out of range");
                    }
                    currList.add(program[inst.xPc]);
                    break;
                case OpCode::SPLIT:
                    if (inst.xPc > program.size() - 1) {
                        throw InvalidPC("First argument to SPLIT Instruction at PC " + std::to_string(pc) + ", is out of range");
                    }
                    if (inst.yPc > program.size() - 1) {
                        throw InvalidPC("Second argument to SPLIT Instruction at PC " + std::to_string(pc) + ", is out of range");
                    }
                    currList.add(program[inst.xPc]);
                    currList.add(program[inst.yPc]);
                    break;
            }

        }

#ifdef DEBUG
        std::cout << "BEFORE SWAP" << std::endl;
        std::cout << "Current List: " << currList << std::endl;
        std::cout << "Next List: " << nextList << std::endl;
#endif

        // Swap the 2 lists
        currList.setListType(ListType::NEXT);
        nextList.setListType(ListType::CURRENT);
        std::swap(currList, nextList);

#ifdef DEBUG
        std::cout << "AFTER SWAP" << std::endl;
        std::cout << "Current List: " << currList << std::endl;
        std::cout << "Next List: " << nextList << std::endl;
#endif

        // Clear the next list
        nextList.clear();

#ifdef DEBUG
        std::cout << "AFTER CLEARING NEXT LIST" << std::endl;
        std::cout << "Next List: " << nextList << std::endl;
        std::cout << "Curr List Size: " << currList.size() << std::endl;
        std::cout << "Match PC: " << matchPc << std::endl;
        std::cout << "Swapped Lists" << std::endl;
#endif

        if (currList.empty() && matchPc != -1) {        // If there was a match and states were exhausted
            Match match = Match(matchPc, input, startSp, matchSp);
            matches.push_back(match);
            for (Instruction &inst : program) {
                inst.listType = ListType::NONE;
            }
            currList.add(program[0]);
            startSp = sp;
            matchPc = -1;
            sp -= 1;
        }
    }
#ifdef DEBUG
    std::cout << "Matches Size: " << matches.size() << std::endl;
#endif


    // Check if all the text matched.
    if (matchSp == input.size()) {
        // Print all the matches.
        for (Match &m : matches) {
            std::cout << m << std::endl;
        }
        return 0;
    } else {
        std::cerr << "lexing error" << std::endl;
        return 1;
    }
}
