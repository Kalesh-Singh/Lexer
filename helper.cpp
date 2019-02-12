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
        throw "Invalid OpCode";
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
        throw "Ambiguous instruction (Extraneous characters found)";
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
        throw "File not found (could not be opened for reading)";
    }

    return nfaProgram;
}

std::string join(const std::vector<std::string> &v, char ch) {
    std::string str = "";
    for (int i = 0; i < v.size(); i++) {
        str += v[i];
        if (i != v.size()-1){
            str += ch;
        }
    }
    return str;
}
