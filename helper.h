//
// Created by kalesh on 2/3/19.
//

// #define DEBUG   // Uncomment for debugging print outs

#ifndef THOMPSONVM_HELPER_H
#define THOMPSONVM_HELPER_H

#include "types.h"
#include <fstream>
#include <sstream>

OpCode getOpCode(const std::string &opCodeStr);
Instruction getInstruction(const std::string &instString);
std::vector<Instruction> getNfaProgram(std::string &nfaPath);
std::string join(const std::vector<std::string> &v, char ch);

#endif //THOMPSONVM_HELPER_H
