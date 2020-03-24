#include "pch.h"
#include "../src/piece.h"
#include "../src/piece.cpp"

using namespace testing;

class APiece : public Test {
 public:
  Piece* piece = new King(true);

};
TEST_F(APiece, isWhiteFunction) {
  EXPECT_TRUE(piece->isWhite());
}