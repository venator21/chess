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

TEST_F(ChessBoard, DistributesPiecesDuringInitialization) {
  board.initializeBoard();
  EXPECT_EQ(board.getSquare(5, 6).getPiece()->getPieceType(), PieceType::PAWN);
  EXPECT_EQ(board.getSquare(4, 7).getPiece()->getPieceType(), PieceType::KING);

  EXPECT_EQ(board.getSquare(0, 0).getPiece()->getPieceType(), PieceType::ROOK);
  EXPECT_EQ(board.getSquare(3, 3).getPiece(), nullptr);
}


TEST_F(ChessBoard, CastelingValidWhiteKing) {
  board.initializeGrid();
  board.grid[4][0].setPiece(board.pieceFactory.Create(WHITE, KING));
  board.grid[7][0].setPiece(board.pieceFactory.Create(WHITE, ROOK));
  board.grid[0][0].setPiece(board.pieceFactory.Create(WHITE, ROOK));

  EXPECT_TRUE(board.isValidCastling(board, board.getSquare(4, 0), board.getSquare(7, 0)));
  EXPECT_TRUE(board.isValidCastling(board, board.getSquare(4, 0), board.getSquare(0, 0)));
}

TEST_F(ChessBoard, CastelingValidBlackKing) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));

  EXPECT_TRUE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(7, 7)));
  EXPECT_TRUE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(0, 7)));
}

TEST_F(ChessBoard, DenyCastelingWhenPathBlocked) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[6][7].setPiece(board.pieceFactory.Create(BLACK, BISHOP));
  board.grid[1][7].setPiece(board.pieceFactory.Create(BLACK, BISHOP));

  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(7, 7)));
  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(0, 7)));
}

TEST_F(ChessBoard, DenyCastelingWhenNoRook) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));

  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(7, 7)));
  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(0, 7)));
}

TEST_F(ChessBoard, DenyCastelingWhenKingMovedAlready) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[4][7].getPiece()->setFirstMoved();

  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(7, 7)));
  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(0, 7)));
}

TEST_F(ChessBoard, DenyCastelingWhenRookMovedAlready) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[7][7].getPiece()->setFirstMoved();
  board.grid[0][7].getPiece()->setFirstMoved();

  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(7, 7)));
  EXPECT_FALSE(board.isValidCastling(board, board.getSquare(4, 7), board.getSquare(0, 7)));
}