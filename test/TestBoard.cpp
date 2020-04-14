#include "gtest/gtest.h"
#include"../src/Board.h"
#include"../src/Board.cpp"
#include"../src/Player.h"
#include"../src/Player.cpp"
#include"../src/Move.h"
#include"../src/Move.cpp"

using namespace testing;

class ChessBoard : public Test {
 public:
   Board board;
   Player player;
};

class ChessEnPassant : public Test {
public:
  PieceFactory pieceFactory;
  Board board;
  Player b_player = HumanPlayer(false);
  Player w_player = HumanPlayer(true);
  Move move = Move(b_player, 2, 6, 2, 4, pieceFactory.Create(BLACK, PAWN), nullptr);
};

TEST_F(ChessBoard, AllowMovementWhenNoPiececInWay) {
  board.initializeBoard();
  EXPECT_TRUE(board.isMovementPathClear(3, 1, 3, 5));
};

TEST_F(ChessBoard, DenyHorizontalMovementWhenOtherPiecesInWay) {
  board.initializeBoard();
  EXPECT_FALSE(board.isMovementPathClear(3, 0, 7, 0));
  EXPECT_FALSE(board.isMovementPathClear(3, 0, 1, 0));
};

TEST_F(ChessBoard, DenyVerticalMovementWhenOtherPiecesInWay) {
  board.initializeBoard();
  EXPECT_FALSE(board.isMovementPathClear(3, 0, 3, 7));
  EXPECT_FALSE(board.isMovementPathClear(5, 7, 5, 0));
};

TEST_F(ChessBoard, DenyDiagonalMovementWhenOtherPiecesInWay) {
  board.initializeBoard();
  EXPECT_FALSE(board.isMovementPathClear(3, 0, 7, 4));
  EXPECT_FALSE(board.isMovementPathClear(3, 0, 0, 3));
  EXPECT_FALSE(board.isMovementPathClear(3, 7, 7, 3));
  EXPECT_FALSE(board.isMovementPathClear(3, 7, 0, 4));

};

TEST_F(ChessBoard, DistributesPiecesDuringInitialization) {
  board.initializeBoard();
  EXPECT_EQ(board.getSquare(5, 6).getPiece()->getPieceType(), PieceType::PAWN);
  EXPECT_EQ(board.getSquare(4, 7).getPiece()->getPieceType(), PieceType::KING);
  EXPECT_EQ(board.getSquare(0, 1).getPiece()->getPieceType(), PieceType::PAWN);

  EXPECT_EQ(board.getSquare(0, 0).getPiece()->getPieceType(), PieceType::ROOK);
  EXPECT_EQ(board.getSquare(3, 3).getPiece(), nullptr);
  EXPECT_EQ(board.getSquare(0, 3).getPiece(), nullptr);
}


TEST_F(ChessBoard, CastelingValidWhiteKing) {
  board.initializeGrid();
  board.grid[4][0].setPiece(board.pieceFactory.Create(WHITE, KING));
  board.grid[7][0].setPiece(board.pieceFactory.Create(WHITE, ROOK));
  board.grid[0][0].setPiece(board.pieceFactory.Create(WHITE, ROOK));

  EXPECT_TRUE(board.isValidCastling(4, 0, 6, 0));
  EXPECT_TRUE(board.isValidCastling(4, 0, 2, 0));
}

TEST_F(ChessBoard, CastelingValidBlackKing) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));

  EXPECT_TRUE(board.isValidCastling(4, 7, 6, 7));
  EXPECT_TRUE(board.isValidCastling(4, 7, 2, 7));
}

TEST_F(ChessBoard, DenyCastelingWhenPathBlocked) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[6][7].setPiece(board.pieceFactory.Create(BLACK, BISHOP));
  board.grid[1][7].setPiece(board.pieceFactory.Create(BLACK, BISHOP));

  EXPECT_FALSE(board.isValidCastling(4, 7, 6, 7));
  EXPECT_FALSE(board.isValidCastling(4, 7, 2, 7));
}

TEST_F(ChessBoard, DenyCastelingWhenNoRook) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));

  EXPECT_FALSE(board.isValidCastling(4, 7, 6, 7));
  EXPECT_FALSE(board.isValidCastling(4, 7, 2, 7));
}

TEST_F(ChessBoard, DenyCastelingWhenKingMovedAlready) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[4][7].getPiece()->setFirstMoved();

  EXPECT_FALSE(board.isValidCastling(4, 7, 6, 7));
  EXPECT_FALSE(board.isValidCastling(4, 7, 2, 7));
}

TEST_F(ChessBoard, DenyCastelingWhenRookMovedAlready) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[0][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.grid[7][7].getPiece()->setFirstMoved();
  board.grid[0][7].getPiece()->setFirstMoved();

  EXPECT_FALSE(board.isValidCastling(4, 7, 6, 7));
  EXPECT_FALSE(board.isValidCastling(4, 7, 2, 7));
}

TEST_F(ChessBoard, RookIsMovedDuringCastlingMove) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.executeCastlingMove(4, 7, 6, 7);

  EXPECT_EQ(board.getSquare(7, 7).getPiece(), nullptr);
  EXPECT_EQ(board.getSquare(5, 7).getPiece()->getPieceType(), ROOK);
}

TEST_F(ChessBoard, CastlingIsProccessedInMakeMove) {
  board.initializeGrid();
  board.grid[4][7].setPiece(board.pieceFactory.Create(BLACK, KING));
  board.grid[7][7].setPiece(board.pieceFactory.Create(BLACK, ROOK));
  board.makeMove(player, 4, 7, 6, 7);

  EXPECT_EQ(board.getSquare(7, 7).getPiece(), nullptr);
  EXPECT_EQ(board.getSquare(5, 7).getPiece()->getPieceType(), ROOK);
  EXPECT_EQ(board.getSquare(6, 7).getPiece()->getPieceType(), KING);
}

TEST_F(ChessBoard, AllowValidMoveToTakePlace) {
  board.initializeBoard();
  board.makeMove(player, 0, 1, 0, 3);
  EXPECT_EQ(board.grid[0][1].getPiece(), nullptr);
  EXPECT_EQ(board.grid[0][3].getPiece()->getPieceType(), PAWN);
}

TEST_F(ChessBoard, DenyMakingMoveWhenStartingSquareEmpty) {
  board.initializeBoard();
  EXPECT_FALSE(board.makeMove(player, 0, 3, 0, 4));
}

TEST_F(ChessBoard, DenyMakingMoveWhenPiecesInWayExceptKnight) {
  board.initializeBoard();
  EXPECT_FALSE(board.makeMove(player, 0, 0, 0, 4));
  EXPECT_TRUE(board.makeMove(player, 1, 0, 0, 2)); // knight should be able to jump over pieces
}

TEST_F(ChessBoard, DenyMakingMoveWhenPiecesMovementRulesWereBroke) {
  board.initializeBoard();
  EXPECT_FALSE(board.makeMove(player, 0, 1, 0, 5));
}

TEST_F(ChessEnPassant, RecognizeEnPassantMoveIsPossible) {
  board.movesPlayed.push_back(move);
  board.grid[2][6].setPiece(board.pieceFactory.Create(BLACK, PAWN));
  board.grid[1][4].setPiece(board.pieceFactory.Create(WHITE, PAWN));

  EXPECT_TRUE(board.isEnPassant(1, 4, 2, 5));
}

TEST_F(ChessEnPassant, ExecutesEnPassantMove) {
  board.movesPlayed.push_back(move);
  board.grid[2][6].setPiece(board.pieceFactory.Create(BLACK, PAWN));
  board.grid[1][4].setPiece(board.pieceFactory.Create(WHITE, PAWN));
  board.makeMove(b_player, 2, 6, 2, 4);
  board.makeMove(w_player, 1, 4, 2, 5);

  EXPECT_EQ(board.getSquare(2, 4).getPiece(), nullptr);
  EXPECT_EQ(board.getSquare(2, 5).getPiece()->getPieceType(), PAWN);
}

