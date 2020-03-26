#include"pch.h"
#include"../src/Board.h"
#include"../src/Board.cpp"
#include"../src/Square.h"
#include"../src/Square.cpp"

using namespace testing;

class ChessBoard : public Test {
 public:
   Board board;
};

TEST_F(ChessBoard, DenyHorizontalMovementWhenOtherPiecesInWay) {
  board.initializeBoard();
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 0, 7, 0));
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 0, 1, 0));
};

TEST_F(ChessBoard, DenyVerticalMovementWhenOtherPiecesInWay) {
  board.initializeBoard();
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 0, 3, 7));
  EXPECT_FALSE(board.isMovementPathClear(board, 5, 7, 5, 0));
};

TEST_F(ChessBoard, DenyDiagonalMovementWhenOtherPiecesInWay) {
  board.initializeBoard();
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 0, 7, 4));
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 0, 0, 3));
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 7, 7, 3));
  EXPECT_FALSE(board.isMovementPathClear(board, 3, 7, 0, 4));

};


TEST_F(ChessBoard, isValidCastling) { //TODO
  board.initializeGrid();
};
