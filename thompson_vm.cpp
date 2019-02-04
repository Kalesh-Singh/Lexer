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

    currList.add(Thread(program[pc]));
    for (unsigned int sp = 0;  sp < input.size(); sp++) {
        for (unsigned long thread = 0; thread < currList.size(); thread++) {
            const Instruction &inst = currList[thread].inst;
            pc = inst.pc;
            switch (inst.opCode) {
                case OpCode::CHAR:
                    if (input[sp] < inst.ch &&  input[sp] > inst.ch2) {
                        break;
                    }
                    nextList.add(Thread(program[pc+1]));
                    break;
                case OpCode::MATCH:
                    // TODO: Handle prefix matches here.
                    if (matchSp < sp) {         // If the match was shorter than the current match
                            matchPc = pc;
                            matchSp = sp;
                    } else if (matchPc > pc) {      // Resetting the matchSp from previous runs
                            matchPc = pc;
                            matchSp = sp;
                    }
                    break;
                case OpCode::JMP:
                    currList.add(Thread(program[inst.xPc]));
                    break;
                case OpCode::SPLIT:
                    currList.add(Thread(program[inst.xPc]));
                    currList.add(Thread(program[inst.yPc]));
                    break;
            }

        }
        // Swap the 2 lists
        currList.setListType(ListType::NEXT);
        nextList.setListType(ListType::CURRENT);
        std::swap(currList, nextList);

        // Clear the next list
        nextList.clear();

        if (currList.empty() && matchPc != -1) {        // If there was a match and states were exhausted
            Match match = Match(matchPc, input, startSp, matchSp);
            matches.push_back(match);
            currList.add(Thread(program[0]));
            startSp = sp;
            matchPc = -1;
            sp -= 1;
        }
    }
    // Print all the matches.
    for (Match &m : matches) {
        std::cout << m << std::endl;
    }

    // Check if all the text matched.
    if (matchSp == input.size()) {
        return 0;
    } else {
        return 1;
    }
}
