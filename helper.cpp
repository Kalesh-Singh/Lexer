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

    unsigned int pc;
    OpCode opCode;
    int ch;
    int ch2;
    unsigned int xPc;
    unsigned int yPc;

    std::string opCodeStr;
    Instruction instruction;

    ss >> pc >> opCodeStr;

    opCode = getOpCode(opCodeStr);

    switch (opCode) {
        case OpCode::CHAR:
            ss >> ch >> ch2;
            if (ch != ch2) {
                // TODO: Throw an exception.
            }
            instruction = Instruction(pc, opCode, (char) ch, (char) ch2);
            break;
        case OpCode::MATCH:
            instruction = Instruction(pc, opCode);
            break;
        case OpCode::JMP:
            ss >> xPc;
            instruction = Instruction(pc, opCode, xPc);
            break;
        case OpCode::SPLIT:
            ss >> xPc >> yPc;
            instruction = Instruction(pc, opCode, xPc, yPc);
            break;
    }

    if (!ss.str().empty()) {
        // TODO: Throw an exception.
    }
#ifdef DEBUG
    std::cout << instruction;
#endif

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
        std::cout << "ERR: Could not open file." << std::endl;
    }

    return nfaProgram;
}
