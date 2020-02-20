#include"board.h"

Board::Board() {
	this->resetBoard();
}

Square Board::getSquare(int x, int y) {
	return grid[x][y];
}

void Board::resetBoard() {

	grid[0][0] = Square(0, 0, new Rook(true));
	grid[1][0] = Square(1, 0, new Knight(true));
	grid[2][0] = Square(2, 0, new Bishop(true));
	grid[3][0] = Square(3, 0, new Queen(true));
	grid[4][0] = Square(4, 0, new King(true));
	grid[5][0] = Square(5, 0, new Bishop(true));
	grid[6][0] = Square(6, 0, new Knight(true));
	grid[7][0] = Square(7, 0, new Rook(true));

	grid[0][1] = Square(0, 1, new Pawn(true));
	grid[1][1] = Square(1, 1, new Pawn(true));
	grid[2][1] = Square(2, 1, new Pawn(true));
	grid[3][1] = Square(3, 1, new Pawn(true));
	grid[4][1] = Square(4, 1, new Pawn(true));
	grid[5][1] = Square(5, 1, new Pawn(true));
	grid[6][1] = Square(6, 1, new Pawn(true));
	grid[7][1] = Square(7, 1, new Pawn(true));

	grid[0][7] = Square(0, 7, new Rook(false));
	grid[1][7] = Square(1, 7, new Knight(false));
	grid[2][7] = Square(2, 7, new Bishop(false));
	grid[3][7] = Square(3, 7, new Queen(false));
	grid[4][7] = Square(4, 7, new King(false));
	grid[5][7] = Square(5, 7, new Bishop(false));
	grid[6][7] = Square(6, 7, new Knight(false));
	grid[7][7] = Square(7, 7, new Rook(false));

	grid[0][6] = Square(0, 6, new Pawn(false));
	grid[1][6] = Square(1, 6, new Pawn(false));
	grid[2][6] = Square(2, 6, new Pawn(false));
	grid[3][6] = Square(3, 6, new Pawn(false));
	grid[4][6] = Square(4, 6, new Pawn(false));
	grid[5][6] = Square(5, 6, new Pawn(false));
	grid[6][6] = Square(6, 6, new Pawn(false));
	grid[7][6] = Square(7, 6, new Pawn(false));
}