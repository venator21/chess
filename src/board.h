#pragma once
#include"square.h"

class Board {
private:
	Square grid[8][8];

public:
	Board();
	void resetBoard();
	Square getSquare(int x, int y);

};