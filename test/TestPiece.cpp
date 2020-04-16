#include "gtest/gtest.h"
#include "../src/Piece.h"
#include "../src/Piece.cpp"

#include <memory>

using namespace testing;

class PieceCollection : public Test {
public:
    King king{King(true)};
    Queen queen{Queen(true)};
    Bishop bishop{Bishop(true)};
    Knight knight{Knight(true)};
    Rook rook{Rook(true)};
    Pawn pawn{Pawn(true)};
    std::shared_ptr<Piece> w_dummy{new Pawn{true}};
    std::shared_ptr<Piece> b_dummy{new Pawn{true}};
};

TEST_F(PieceCollection, KingMovesOneSquareEachDirection) {
    EXPECT_TRUE(king.canMove(nullptr, nullptr, 3, 3, 4, 4));
    EXPECT_TRUE(king.canMove(nullptr, nullptr, 3, 3, 3, 4));
    EXPECT_TRUE(king.canMove(nullptr, nullptr, 3, 3, 2, 2));
    EXPECT_TRUE(king.canMove(nullptr, nullptr, 3, 3, 3, 4));

    EXPECT_FALSE(king.canMove(nullptr, nullptr, 3, 3, 5, 4));
    EXPECT_FALSE(king.canMove(nullptr, nullptr, 3, 3, 6, 6));
    EXPECT_FALSE(king.canMove(nullptr, nullptr, 3, 3, 1, 2));
    EXPECT_FALSE(king.canMove(nullptr, nullptr, 3, 3, 3, 0));
}

TEST_F(PieceCollection, QueenMovesDiagonalAndLinear) {
    EXPECT_TRUE(queen.canMove(nullptr, nullptr, 3, 3, 7, 7));
    EXPECT_TRUE(queen.canMove(nullptr, nullptr, 3, 3, 1, 5));
    EXPECT_TRUE(queen.canMove(nullptr, nullptr, 3, 3, 3, 7));
    EXPECT_TRUE(queen.canMove(nullptr, nullptr, 3, 3, 0, 3));

    EXPECT_FALSE(queen.canMove(nullptr, nullptr, 3, 3, 5, 4));
    EXPECT_FALSE(queen.canMove(nullptr, nullptr, 3, 3, 2, 6));
    EXPECT_FALSE(queen.canMove(nullptr, nullptr, 3, 3, 0, 5));
    EXPECT_FALSE(queen.canMove(nullptr, nullptr, 3, 3, 2, 1));
}

TEST_F(PieceCollection, BishopMovesOnlyDiagonal) {
    EXPECT_TRUE(bishop.canMove(nullptr, nullptr, 3, 3, 1, 5));
    EXPECT_TRUE(bishop.canMove(nullptr, nullptr, 3, 3, 5, 5));
    EXPECT_TRUE(bishop.canMove(nullptr, nullptr, 3, 3, 5, 1));
    EXPECT_TRUE(bishop.canMove(nullptr, nullptr, 3, 3, 1, 1));

    EXPECT_FALSE(bishop.canMove(nullptr, nullptr, 3, 3, 0, 3));
    EXPECT_FALSE(bishop.canMove(nullptr, nullptr, 3, 3, 3, 0));
    EXPECT_FALSE(bishop.canMove(nullptr, nullptr, 3, 3, 6, 3));
    EXPECT_FALSE(bishop.canMove(nullptr, nullptr, 3, 3, 3, 6));
}

TEST_F(PieceCollection, RookMovesOnlyLinear) {
    EXPECT_TRUE(rook.canMove(nullptr, nullptr, 3, 3, 0, 3));
    EXPECT_TRUE(rook.canMove(nullptr, nullptr, 3, 3, 3, 0));
    EXPECT_TRUE(rook.canMove(nullptr, nullptr, 3, 3, 6, 3));
    EXPECT_TRUE(rook.canMove(nullptr, nullptr, 3, 3, 3, 6));

    EXPECT_FALSE(rook.canMove(nullptr, nullptr, 3, 3, 1, 5));
    EXPECT_FALSE(rook.canMove(nullptr, nullptr, 3, 3, 5, 5));
    EXPECT_FALSE(rook.canMove(nullptr, nullptr, 3, 3, 5, 1));
    EXPECT_FALSE(rook.canMove(nullptr, nullptr, 3, 3, 1, 1));
}

TEST_F(PieceCollection, KnightMovesInShapeOfLetterL) {
    EXPECT_TRUE(knight.canMove(nullptr, nullptr, 3, 3, 5, 4));
    EXPECT_TRUE(knight.canMove(nullptr, nullptr, 3, 3, 2, 1));
    EXPECT_TRUE(knight.canMove(nullptr, nullptr, 3, 3, 1, 4));
    EXPECT_TRUE(knight.canMove(nullptr, nullptr, 3, 3, 4, 1));


    EXPECT_FALSE(knight.canMove(nullptr, nullptr, 3, 3, 1, 5));
    EXPECT_FALSE(knight.canMove(nullptr, nullptr, 3, 3, 5, 5));
    EXPECT_FALSE(knight.canMove(nullptr, nullptr, 3, 3, 3, 0));
    EXPECT_FALSE(knight.canMove(nullptr, nullptr, 3, 3, 6, 3));
}

TEST_F(PieceCollection, PawnMovesOnlyForward) {
    EXPECT_FALSE(pawn.canMove(w_dummy, nullptr, 3, 3, 3, 2));
    EXPECT_TRUE(pawn.canMove(w_dummy, nullptr, 3, 3, 3, 4));
}

TEST_F(PieceCollection, PawnMovesTwoSquersOnlyFirstMove) {
    EXPECT_TRUE(pawn.canMove(w_dummy, nullptr, 3, 3, 3, 5));

    pawn.setFirstMoved();
    EXPECT_FALSE(pawn.canMove(w_dummy, nullptr, 3, 3, 3, 5));
}

TEST_F(PieceCollection, PawnMovesOneSquereDiagonalOnlyWhenGoingForKill) {
    EXPECT_FALSE(pawn.canMove(w_dummy, nullptr, 3, 3, 4, 4));
    EXPECT_TRUE(pawn.canMove(w_dummy, b_dummy, 3, 3, 4, 4));
}