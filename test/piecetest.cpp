#include "pch.h"
#include "../src/piece.h"
#include "../src/piece.cpp"


using namespace testing;

//abstract class Piece generic implementation for testing purposes
class PieceTest : public Piece {
public:
  PieceTest(bool white) : Piece{ white } {};
  virtual PieceType getPieceType() { return this->pieceType; };
  virtual bool canMove(Piece* sourcePiece, Piece* killedPiece,
    int sourceX, int sourceY,
    int killedX, int killedY) { return 1; };
 private:
   PieceType pieceType = PieceType::PIECETEST;
};

class ChessPiece : public Test {
public:
  PieceTest piece = PieceTest(true);
};

TEST_F(ChessPiece, ReturnsColorInformation) {
  ASSERT_TRUE(piece.isWhite());
}

TEST_F(ChessPiece, SetsItsColor) {
  bool white = false;
  piece.setWhite(white);
  ASSERT_EQ(piece.isWhite(), white);
}

TEST_F(ChessPiece, ReturnsInformationAboutBeingKilled) {
  ASSERT_FALSE(piece.isKilled());
}

TEST_F(ChessPiece, SetsKilledFlag) {
  bool killed = true;
  piece.setKilled(killed);
  ASSERT_EQ(piece.isKilled(), killed);
}

TEST_F(ChessPiece, ReturnInformationIfPieceMovedAlready) {
  ASSERT_TRUE(piece.isFirstMove());
}

TEST_F(ChessPiece, SetsFirstMoveFlag) {
  piece.setFirstMoved();
  ASSERT_FALSE(piece.isFirstMove());
}

TEST_F(ChessPiece, ComparesColorsOfTwoPieces) {
  Piece* w_dummy = new Pawn(true);
  Piece* b_dummy = new Pawn(false);
  EXPECT_FALSE(piece.isPotentialKillSameColor(w_dummy, b_dummy));
}


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

TEST_F(PieceCollection, ReturnsAppriopriatePieceTypeValue) {
  EXPECT_EQ(king.getPieceType(), PieceType::KING);
  EXPECT_EQ(queen.getPieceType(), PieceType::QUEEN);
  EXPECT_EQ(bishop.getPieceType(), PieceType::BISHOP);
  EXPECT_EQ(knight.getPieceType(), PieceType::KNIGHT);
  EXPECT_EQ(rook.getPieceType(), PieceType::ROOK);
  EXPECT_EQ(pawn.getPieceType(), PieceType::PAWN);
}

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