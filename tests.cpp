//
// Created by Kaleshwar Singh on 2019-02-11.
//

#include <gtest/gtest.h>
#include "helper.h"

// Invalid pathname for NFA Program
TEST(GetNfaProgramTest, testInvalidFilePath) {
    std::string invalidPath = "!%,-+#&";
    EXPECT_THROW(getNfaProgram(invalidPath), FileNotFound);
}

class InstructionTest : public testing::Test {
public:
    const std::string insts[2] = {
            "a CHAR 10 10",         // Invalid instruction number (pc)
            "1 BLAH 10 10"          // Invalid Op Code
    };
};

TEST_F(InstructionTest, testInvalidInstNum) {
    EXPECT_THROW(getInstruction(insts[0]), MalformedInstruction);
}

TEST_F(InstructionTest, testInvalidOpCode) {
    EXPECT_THROW(getInstruction(insts[1]), InvalidOpCode);
}

class CharInstructionTest : public testing::Test {
public:
    const std::string charInsts[7] = {
            "0 CHAR 10 10",     // Valid 1 char
            "0 CHAR 10 12",     // Valid range
            "0 CHAR a 10",      // Invalid 1st operand
            "0 CHAR 10 a",      // Invalid 2nd operand
            "0 CHAR a a",       // Both operand invalid
            "0 CHAR 10 10 10",  // Extraneous characters
            "0 CHAR 12 10",     // Invalid range

    };
};

TEST_F(CharInstructionTest, testValidSingleChar) {
    Instruction inst = Instruction(0, OpCode::CHAR, (char) 10, (char) 10);
    EXPECT_EQ(inst, getInstruction(charInsts[0]));
}

TEST_F(CharInstructionTest, testValidCharRange) {
    Instruction inst = Instruction(0, OpCode::CHAR, (char) 10, (char) 12);
    EXPECT_EQ(inst, getInstruction(charInsts[1]));
}

TEST_F(CharInstructionTest, testInvalidFirstOperand) {
    EXPECT_THROW(getInstruction(charInsts[2]), MalformedInstruction);
}

TEST_F(CharInstructionTest, testInvalidSecondOperand) {
    EXPECT_THROW(getInstruction(charInsts[3]), MalformedInstruction);
}

TEST_F(CharInstructionTest, testBothOperandsInvalid) {
    EXPECT_THROW(getInstruction(charInsts[4]), MalformedInstruction);
}

TEST_F(CharInstructionTest, testExtraneousChars) {
    EXPECT_THROW(getInstruction(charInsts[5]), MalformedInstruction);
}

TEST_F(CharInstructionTest, testInvalidCharRange) {
    EXPECT_THROW(getInstruction(charInsts[6]), MalformedInstruction);
}

class MatchInstructionTest : public testing::Test {
public:
    const std::string matchInsts[2] = {
            "0 MATCH",          // Valid
            "0 MATCH 10"        // Extraneous characters
    };
};

TEST_F(MatchInstructionTest, testValidMatchInst) {
    Instruction inst = Instruction(0, OpCode::MATCH);
    EXPECT_EQ(inst, getInstruction(matchInsts[0]));
}

TEST_F(MatchInstructionTest, testExtraneousChars) {
    EXPECT_THROW(getInstruction(matchInsts[1]), MalformedInstruction);
}

class JmpInstructionTest : public testing::Test {
public:
    const std::string jmpInsts[3] = {
            "0 JMP 10",         // Valid
            "0 JMP a",          // Invalid operand
            "0 JMP 10 10"       // Extraneous characters
    };
};

TEST_F(JmpInstructionTest, testValidJmpInst) {
    Instruction inst = Instruction(0, OpCode::JMP, 10);
    EXPECT_EQ(inst, getInstruction(jmpInsts[0]));
}

TEST_F(JmpInstructionTest, testInvalidOperand) {
    EXPECT_THROW(getInstruction(jmpInsts[1]), MalformedInstruction);
}

TEST_F(JmpInstructionTest, testExtraneousChars) {
    EXPECT_THROW(getInstruction(jmpInsts[2]), MalformedInstruction);
}

class SplitInstructionTest : public testing::Test {
public:
    const std::string splitInsts[5] = {
            "0 SPLIT 10 12",    // Valid
            "0 SPLIT a 10",      // Invalid 1st operand
            "0 SPLIT 10 a",      // Invalid 2nd operand
            "0 SPLIT a B",       // Both operand invalid
            "0 SPLIT 10 12 10",  // Extraneous characters
    };
};

TEST_F(SplitInstructionTest, testValidSplitInst) {
    Instruction inst = Instruction(0, OpCode::SPLIT, (unsigned) 10, (unsigned) 12);
    EXPECT_EQ(inst, getInstruction(splitInsts[0]));
}

TEST_F(SplitInstructionTest, testInvalidFirstOperand) {
    EXPECT_THROW(getInstruction(splitInsts[1]), MalformedInstruction);
}

TEST_F(SplitInstructionTest, testInvalidSecondOperand) {
    EXPECT_THROW(getInstruction(splitInsts[2]), MalformedInstruction);
}

TEST_F(SplitInstructionTest, testBothOperandsInvalid) {
    EXPECT_THROW(getInstruction(splitInsts[3]), MalformedInstruction);
}

TEST_F(SplitInstructionTest, testExtraneousChars) {
    EXPECT_THROW(getInstruction(splitInsts[4]), MalformedInstruction);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}