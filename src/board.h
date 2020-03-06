#pragma once
#include"square.h"
#include"piece.h"

class Board {
 public:
  Board();
  void initializeBoard();
  Square* getSquare(int x, int y);
  bool isMovementPathClear(Board board,
                           int sourceX, int sourceY,
                           int killedX, int killedY);
 private:
	Square** grid = new Square* [8];
};