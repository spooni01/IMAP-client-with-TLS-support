#include <gtest/gtest.h>

#include "../../src/main.hpp"

#include "test_exceptions.cpp"
#include "test_ArgsParser.cpp"
#include "test_AuthManager.cpp"
#include "test_Message.cpp"
#include "test_FiniteStateMachine.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}