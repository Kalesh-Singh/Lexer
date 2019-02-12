//
// Created by Kaleshwar Singh on 2019-02-11.
//

#include <gtest/gtest.h>
#include "helper.h"

class GetInstructionTest : public testing::Test {
public:
    const std::string insts[4] = {
            "0 CHAR 10 10",
            "1 MATCH",
            "2 SPLIT 0 1",
            "3 JMP 1",

    };

};

TEST_F(GetInstructionTest, testGetValidCharInstruction) {
    Instruction inst = Instruction(0, OpCode::CHAR, (char) 10, (char) 10);
    EXPECT_EQ(inst, getInstruction(insts[0]));
}

TEST_F(GetInstructionTest, testGetValidMatchInstruction) {
    Instruction inst = Instruction(1, OpCode::MATCH);
    EXPECT_EQ(inst, getInstruction(insts[1]));
}

TEST_F(GetInstructionTest, testGetValidSplitInstruction) {
    Instruction inst = Instruction(2, OpCode::SPLIT, (unsigned) 0, (unsigned) 1);
    EXPECT_EQ(inst, getInstruction(insts[2]));
}

TEST_F(GetInstructionTest, testGetValidJmpInstruction) {
    Instruction inst = Instruction(3, OpCode::JMP, 1);
    EXPECT_EQ(inst, getInstruction(insts[3]));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}