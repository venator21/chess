#include "gtest/gtest.h"
#include "TestPiece.cpp"
#include "TestSquare.cpp"
#include "TestBoard.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
