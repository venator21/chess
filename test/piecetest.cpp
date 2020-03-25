#include "pch.h"
#include "../src/piece.h"
#include "../src/piece.cpp"


using namespace testing;

class PieceCollection : public Test {
public:
  King king = King(true);
  Queen queen = Queen(true);
  Bishop bishop = Bishop(true);
  Knight knight = Knight(true);
  Rook rook = Rook(true);
  Pawn pawn = Pawn(true);
  Piece* w_dummy = new Pawn(true);
  Piece* b_dummy = new Pawn(false);
};

TEST_F(PieceCollection, KingMovesOneSquareEachDirection) {
  EXPECT_TRUE(king.canMove(NULL, NULL, 3, 3, 4, 4));
  EXPECT_TRUE(king.canMove(NULL, NULL, 3, 3, 3, 4));
  EXPECT_TRUE(king.canMove(NULL, NULL, 3, 3, 2, 2));
  EXPECT_TRUE(king.canMove(NULL, NULL, 3, 3, 3, 4));

  EXPECT_FALSE(king.canMove(NULL, NULL, 3, 3, 5, 4));
  EXPECT_FALSE(king.canMove(NULL, NULL, 3, 3, 6, 6));
  EXPECT_FALSE(king.canMove(NULL, NULL, 3, 3, 1, 2));
  EXPECT_FALSE(king.canMove(NULL, NULL, 3, 3, 3, 0));
}

TEST_F(PieceCollection, QueenMovesDiagonalAndLinear) {
  EXPECT_TRUE(queen.canMove(NULL, NULL, 3, 3, 7, 7));
  EXPECT_TRUE(queen.canMove(NULL, NULL, 3, 3, 1, 5));
  EXPECT_TRUE(queen.canMove(NULL, NULL, 3, 3, 3, 7));
  EXPECT_TRUE(queen.canMove(NULL, NULL, 3, 3, 0, 3));

  EXPECT_FALSE(queen.canMove(NULL, NULL, 3, 3, 5, 4));
  EXPECT_FALSE(queen.canMove(NULL, NULL, 3, 3, 2, 6));
  EXPECT_FALSE(queen.canMove(NULL, NULL, 3, 3, 0, 5));
  EXPECT_FALSE(queen.canMove(NULL, NULL, 3, 3, 2, 1));
}

TEST_F(PieceCollection, BishopMovesDiagonal) {
  EXPECT_TRUE(bishop.canMove(NULL, NULL, 3, 3, 1, 5));
  EXPECT_TRUE(bishop.canMove(NULL, NULL, 3, 3, 5, 5));
  EXPECT_TRUE(bishop.canMove(NULL, NULL, 3, 3, 5, 1));
  EXPECT_TRUE(bishop.canMove(NULL, NULL, 3, 3, 1, 1));

  EXPECT_FALSE(bishop.canMove(NULL, NULL, 3, 3, 0, 3));
  EXPECT_FALSE(bishop.canMove(NULL, NULL, 3, 3, 3, 0));
  EXPECT_FALSE(bishop.canMove(NULL, NULL, 3, 3, 6, 3));
  EXPECT_FALSE(bishop.canMove(NULL, NULL, 3, 3, 3, 6));
}

TEST_F(PieceCollection, RookMovesLinear) {
  EXPECT_TRUE(rook.canMove(NULL, NULL, 3, 3, 0, 3));
  EXPECT_TRUE(rook.canMove(NULL, NULL, 3, 3, 3, 0));
  EXPECT_TRUE(rook.canMove(NULL, NULL, 3, 3, 6, 3));
  EXPECT_TRUE(rook.canMove(NULL, NULL, 3, 3, 3, 6));

  EXPECT_FALSE(rook.canMove(NULL, NULL, 3, 3, 1, 5));
  EXPECT_FALSE(rook.canMove(NULL, NULL, 3, 3, 5, 5));
  EXPECT_FALSE(rook.canMove(NULL, NULL, 3, 3, 5, 1));
  EXPECT_FALSE(rook.canMove(NULL, NULL, 3, 3, 1, 1));
}

TEST_F(PieceCollection, KnightMovesInShapeOfLetterL) {
  EXPECT_TRUE(knight.canMove(NULL, NULL, 3, 3, 5, 4));
  EXPECT_TRUE(knight.canMove(NULL, NULL, 3, 3, 2, 1));
  EXPECT_TRUE(knight.canMove(NULL, NULL, 3, 3, 1, 4));
  EXPECT_TRUE(knight.canMove(NULL, NULL, 3, 3, 4, 1));


  EXPECT_FALSE(knight.canMove(NULL, NULL, 3, 3, 1, 5));
  EXPECT_FALSE(knight.canMove(NULL, NULL, 3, 3, 5, 5));
  EXPECT_FALSE(knight.canMove(NULL, NULL, 3, 3, 3, 0));
  EXPECT_FALSE(knight.canMove(NULL, NULL, 3, 3, 6, 3));
}

TEST_F(PieceCollection, PawnMovesOnlyForward) {
  EXPECT_FALSE(pawn.canMove(w_dummy, NULL, 3, 3, 3, 2));
  EXPECT_TRUE(pawn.canMove(w_dummy, NULL, 3, 3, 3, 4));
}

TEST_F(PieceCollection, PawnMovesTwoSquersOnlyFirstMove) {
  EXPECT_TRUE(pawn.canMove(w_dummy, NULL, 3, 3, 3, 5));

  pawn.setFirstMoved();
  EXPECT_FALSE(pawn.canMove(w_dummy, NULL, 3, 3, 3, 5));
}

TEST_F(PieceCollection, PawnMovesOneSquereDiagonalOnlyWhenGoingForKill) {
  EXPECT_FALSE(pawn.canMove(w_dummy, NULL, 3, 3, 4, 4));
  EXPECT_TRUE(pawn.canMove(w_dummy, b_dummy, 3, 3, 4, 4));
}