#include <gtest/gtest.h>

#include "unit/test_ArgsParser.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}