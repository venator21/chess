#pragma once
#include<array>
#include"square.h"
#include"piece.h"

template <class T, size_t ROW, size_t COL >
using Matrix = std::array<std::array<T, COL>, ROW>;


class Board {
 public:
  Board();
  void initializeBoard();
  void initializeGrid();
  void initializePieces();
  Square getSquare(int x, int y);
  bool isMovementPathClear(Board board,
                           int sourceX, int sourceY,
                           int killedX, int killedY);
  bool isValidCastling(Board board, Square startSquare, Square endSquare);

 private:
   Matrix<Square, 8, 8> grid;
   //std::array<std::array<Square, 8>, 8> grid;
   //Square** grid = new Square* [8];
};


