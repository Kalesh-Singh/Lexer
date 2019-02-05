//
// Created by kalesh on 2/3/19.
//

#include "thompson_vm.h"
#include <iostream>         // TODO: Delete

ThompsonVm::ThompsonVm(const std::vector <Instruction> &program, std::string &input) :
    program(program), input(input) {}

int ThompsonVm::tokenize() {
    std::vector<Match> matches;

    int startSp = 0;
    int matchSp = -1;
    int matchPc = -1;

    currList.push(Thread(program[pc]));
    for (unsigned int sp = 0;  sp < input.size(); sp++) {
        while (!currList.empty()) {
            const Instruction &inst = currList.pop().inst;
            pc = inst.pc;
            switch (inst.opCode) {
                case OpCode::CHAR:
                    if (input[sp] < inst.ch &&  input[sp] > inst.ch2) {
                        break;
                    }
                    nextList.push(Thread(program[pc+1]));
                    break;
                case OpCode::MATCH:
                    // TODO: Handle prefix matches here
                    std::cout << "Matched!" << std::endl;
                    if (matchSp < sp) {         // If the match was shorter than the current match
                            matchPc = pc;
                            matchSp = sp;
                    } else if (matchPc > pc) {      // Resetting the matchSp from previous runs
                            matchPc = pc;
                            matchSp = sp;
                    }
                    break;
                case OpCode::JMP:
                    currList.push(Thread(program[inst.xPc]));
                    break;
                case OpCode::SPLIT:
                    currList.push(Thread(program[inst.xPc]));
                    currList.push(Thread(program[inst.yPc]));
                    break;
            }

        }

        std::cout << "BEFORE SWAP" << std::endl;
        std::cout << "Current List: " << currList << std::endl;
        std::cout << "Next List: " << nextList << std::endl;

        // Swap the 2 lists
        currList.setListType(ListType::NEXT);
        nextList.setListType(ListType::CURRENT);
        std::swap(currList, nextList);

        std::cout << "AFTER SWAP" << std::endl;
        std::cout << "Current List: " << currList << std::endl;
        std::cout << "Next List: " << nextList << std::endl;

        // Clear the next list
        nextList.clear();

        std::cout << "AFTER CLEARING NEXT LIST" << std::endl;
        std::cout << "Next List: " << nextList << std::endl;

        std::cout << "Curr List Size: " << currList.size() << std::endl;
        std::cout << "Match PC: " << matchPc << std::endl;

        std::cout << "Swapped Lists" << std::endl;
        if (currList.empty() && matchPc != -1) {        // If there was a match and states were exhausted
            std::cout << "Check for state exhaustion and match" << std::endl;
            Match match = Match(matchPc, input, startSp, matchSp);
            matches.push_back(match);
            currList.push(Thread(program[0]));
            startSp = sp;
            matchPc = -1;
            sp -= 1;
        }
    }

    std::cout << "Matches Size: " << matches.size() << std::endl;
    // Print all the matches.
    for (Match &m : matches) {
        std::cout << m << std::endl;
    }

    // Check if all the text matched.
    return (matchPc == input.size()) ? 0 : 1;
}
