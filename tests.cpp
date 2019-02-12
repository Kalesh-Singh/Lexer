//
// Created by Kaleshwar Singh on 2019-02-11.
//

#include <gtest/gtest.h>
#include "helper.h"

class GetOpCodeTest : public testing::Test {
public:
    const std::string charInstStr = "0 CHAR 10 10\n";
    const std::string matchInstStr = "0 MATCH\n";
    const std::string splitInstStr = "0 SPLIT 2 1\n";
    const std::string jmpInstStr = "0 JMP 5\n";
};

TEST_F(GetOpCodeTest, testGetCharOpCode){
EXPECT_EQ(OpCode::CHAR, getOpCode(charInstStr));
}

TEST_F(GetOpCodeTest, testGetMatchOpCode){
EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}