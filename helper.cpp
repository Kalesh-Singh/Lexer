//
// Created by kalesh on 2/3/19.
//

#include "helper.h"

OpCode getOpCode(const std::string &opCodeStr) {
    if (opCodeStr == "CHAR") {
        return OpCode::CHAR;
    } else if (opCodeStr == "MATCH") {
        return OpCode::MATCH;
    } else if (opCodeStr == "JMP") {
        return OpCode::JMP;
    } else if (opCodeStr == "SPLIT") {
        return OpCode::SPLIT;
    } else {
        // TODO: Throw an exception
    }
}

Instruction getInstruction(const std::string &instString) {
    std::stringstream ss;
    ss << instString;

    unsigned int instNum;
    OpCode opCode;
    char ch;
    unsigned int xInst;
    unsigned int yInst;

    std::string opCodeStr;
    Instruction instruction;

    ss >> instNum >> opCodeStr;

    opCode = getOpCode(opCodeStr);

    switch (opCode) {
        case OpCode::CHAR:
            char ch2;
            ss >> ch >> ch2;
            if (ch != ch2) {
                // TODO: Throw an exception.
            }
            instruction = Instruction(instNum, opCode, ch);
            break;
        case OpCode::MATCH:
            instruction = Instruction(instNum, opCode);
            break;
        case OpCode::JMP:
            ss >> xInst;
            instruction = Instruction(instNum, opCode, xInst);
            break;
        case OpCode::SPLIT:
            ss >> xInst >> yInst;
            instruction = Instruction(instNum, opCode, xInst, yInst);
            break;
    }

    if (!ss.str().empty()) {
        // TODO: Throw an exception.
    }


    return instruction;
}

std::vector<Instruction> getNfaProgram(std::string &nfaPath) {
    std::vector<Instruction> nfaProgram;
    std::string instString;
    std::ifstream nfaFile(nfaPath);

    if (nfaFile.is_open()) {
        while (getline(nfaFile, instString)) {
            // Parse the instruction string
            nfaProgram.push_back(getInstruction(instString));
        }
        nfaFile.close();
    } else {
        // TODO: Throw an exception.
    }


    return std::vector<Instruction>();
}
