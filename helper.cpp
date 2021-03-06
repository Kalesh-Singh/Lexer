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
        throw InvalidOpCode((opCodeStr + " is not a valid op code").c_str());
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

    ss >> pc;
    if (ss.fail()) {
        throw MalformedInstruction(
                ("Expects InstructionNumber to be integer type in Instruction: "
                 + instString).c_str());
    }
    ss >> opCodeStr;
    if (ss.fail() || opCodeStr == "\n") {
        throw MalformedInstruction(
                ("Malformed Op Code in Instruction: " + instString).c_str());
    }

    opCode = getOpCode(opCodeStr);

    switch (opCode) {
        case OpCode::CHAR:
            ss >> ch;
            if (ss.fail()) {
                throw MalformedInstruction(
                        ("CHAR Instruction excepts first operand to be of integer type in Instruction: "
                         + instString).c_str());
            }
            ss >> ch2;
            if (ss.fail()) {
                throw MalformedInstruction(
                        ("CHAR Instruction excepts second operand to be of integer type in Instruction: "
                         + instString).c_str());
            }
            instruction = Instruction(pc, opCode, (char) ch, (char) ch2);
            break;
        case OpCode::MATCH:
            instruction = Instruction(pc, opCode);
            break;
        case OpCode::JMP:
            ss >> xPc;
            if (ss.fail()) {
                throw "Malformed Instruction: " + instString + "\n\n";
            }
            instruction = Instruction(pc, opCode, xPc);
            break;
        case OpCode::SPLIT:
            ss >> xPc;
            if (ss.fail()) {
                throw MalformedInstruction(
                        ("SPLIT Instruction excepts first operand to be of integer type in Instruction: "
                         + instString).c_str());
            }
            ss >> yPc;
            if (ss.fail()) {
                throw MalformedInstruction(
                        ("SPLIT Instruction excepts second operand to be of integer type in Instruction: "
                         + instString).c_str());
            }
            instruction = Instruction(pc, opCode, xPc, yPc);
            break;
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
            if (instString.size() > 0 && instString != "\n") {      // Ignore blank lines
                nfaProgram.push_back(getInstruction(instString));
            }
        }
        nfaFile.close();
    } else {
        throw nfaPath + ": File not found (could not be opened for reading)\n\n";
    }

    return nfaProgram;
}

std::string join(const std::vector<std::string> &v, char ch) {
    std::string str;
    for (int i = 0; i < v.size(); i++) {
        str += v[i];
        if (i != v.size() - 1) {
            str += ch;
        }
    }
    return str;
}
