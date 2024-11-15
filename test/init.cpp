#include <gtest/gtest.h>

#include "../src/main.hpp"

#include "unit/test_ArgsParser.cpp"
#include "unit/test_AuthManager.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}