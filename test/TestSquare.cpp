#include "gtest/gtest.h"
#include "../src/Square.h"
#include "../src/Square.cpp"

using namespace testing;

class ChessSquare: public Test {
public:
  std::shared_ptr<Piece> somePiece = PieceFactory::create(true, PAWN);
  Square occupiedSquare = Square(0, 1, PieceFactory::create(true, PAWN), false);
  Square emptySquare = Square(0, 1, nullptr, false);
};

TEST_F(ChessSquare, SetsOccupiedSquareToNullptr){
  EXPECT_EQ(occupiedSquare.getPiece()->getPieceType(), PieceType::PAWN);
  occupiedSquare.setPiece(nullptr);
  EXPECT_EQ(occupiedSquare.getPiece(), nullptr);
}

TEST_F(ChessSquare, SetsEmptySquareToSomePiece) {
  EXPECT_EQ(emptySquare.getPiece(), nullptr);
  emptySquare.setPiece(somePiece);
  EXPECT_EQ(emptySquare.getPiece()->getPieceType(), PieceType::PAWN);
}

