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
            program[pc].listType = ListType::NONE;
            switch (inst.opCode) {
                case OpCode::CHAR:
                    if (input[sp] == '\r') {
                        std::cout << "DEBUGGING:" << std::endl;
                        std::cout << "Ch1 Value: " << (int) inst.ch <<std::endl;
                        std::cout << "Ch2 Value: " << (int) inst.ch2 <<std::endl;
                        std::cout << "Input Char value: " << (int) input[sp] <<std::endl;
                    }
                    if (sp < input.size() && input[sp] >= inst.ch && input[sp] <= inst.ch2) {
                        nextList.add(program[pc + 1]);
                    }
                    break;
                case OpCode::MATCH:
                    // TODO: Handle prefix matches here

                    if (matchSp < sp) {             // If the match was shorter than the current match
                        matchPc = pc;
                        matchSp = sp;
                    } else if (matchPc > pc) {      // Choose the match that came earlier
                        matchPc = pc;
                        matchSp = sp;
                    }
#ifdef DEBUG
                    std::cout << "Matched: " << matchPc << ": [" << startSp << ", " << matchSp << ")" << std::endl;
#endif
                    break;
                case OpCode::JMP:
                    currList.add(program[inst.xPc]);
                    break;
                case OpCode::SPLIT:
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
#ifdef DEBUG
            std::cout << "Check for state exhaustion and match" << std::endl;
#endif
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
