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

    currList.add(program[0]);

    for (unsigned int sp = 0;  sp <= input.size(); sp++) {
        while (!currList.empty()) {
            const Instruction &inst = currList.pop();
            pc = inst.pc;
            switch (inst.opCode) {
                case OpCode::CHAR:
                    if (sp < input.size()
                        && input[sp] < inst.ch
                        &&  input[sp] > inst.ch2) {
                        break;
                    }
                    nextList.add(program[pc+1]);
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

                    std::cout << "Matched: " << input.substr(startSp, matchSp - startSp) << std::endl;
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
            for (Instruction &inst : program) {
                inst.listType = ListType::NONE;
            }
            currList.add(program[0]);
            startSp = sp;
            matchPc = -1;
            sp -= 1;
            std::cout << "SP = " << sp << std::endl;
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
