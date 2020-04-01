#pragma once
#include<iostream>
#include<vector>
#include<array>
#include <list>
#include<string>
#include"Square.h"
#include"Piece.h"
#include"Player.h"
#include"Move.h"

enum Color {BLACK = 0, WHITE = 1};

template <class T, size_t ROW, size_t COL >
using Matrix = std::array<std::array<T, COL>, ROW>;


class Board {
 public:
  Board();
  void initializeBoard();
  void initializeGrid();
  void initializePieces();
  Square getSquare(int x, int y);
  bool makeMove(Player currnetTurn, int sourceX, int sourceY, int killedX, int killedY);
  void sourcePieceMoved(int sourceX, int sourceY, int destinationX, int destinationY);
  bool isMovementPathClear(int sourceX, int sourceY, int killedX, int killedY);
  void executePromotion(Player currnetTurn, int destinationX, int destinationY);
  bool isValidCastling(int sourceX, int sourceY, int destinationX, int destinationY);
  void executeCastlingMove(int sourceX, int sourceY, int destinationX, int destinationY);
  bool isEnPassant(int sourceX, int sourceY, int destinationX, int destinationY);
  void executeEnPassantMove();
  std::vector<int> EnPassantTarget();
  bool isKingKilled();
  void printBoard();

  Matrix<Square, 8, 8> grid;
  PieceFactory pieceFactory;
  std::list<Move> movesPlayed;
};


