#pragma once
#include"Square.h"
#include"piece.h"

class Board {
private:
	Square** grid = new Square* [8];


public:
	Board();
	void initializeBoard();
	Square* getSquare(int x, int y);
};