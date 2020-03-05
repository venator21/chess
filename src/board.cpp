#include<iostream>
#include"board.h"


using namespace std;

Board::Board() {
	this->initializeBoard();
}

Square* Board::getSquare(int x, int y) {
	return (*(grid + x) + y);
}

void Board::initializeBoard() {
	for (int i = 0; i < 8; ++i) {
		grid[i] = new Square[8];
	}

	*(*(grid + 0) + 0) = Square(0, 0, new Rook(true));
	*(*(grid + 1) + 0) = Square(1, 0, new Knight(true));
	*(*(grid + 2) + 0) = Square(2, 0, new Bishop(true));
	*(*(grid + 3) + 0) = Square(3, 0, new Queen(true));
	*(*(grid + 4) + 0) = Square(4, 0, new King(true));
	*(*(grid + 5) + 0) = Square(5, 0, new Bishop(true));
	*(*(grid + 6) + 0) = Square(6, 0, new Knight(true));
	*(*(grid + 7) + 0) = Square(7, 0, new Rook(true));

	*(*(grid + 0) + 7) = Square(0, 7, new Rook(false));
	*(*(grid + 1) + 7) = Square(1, 7, new Knight(false));
	*(*(grid + 2) + 7) = Square(2, 7, new Bishop(false));
	*(*(grid + 3) + 7) = Square(3, 7, new Queen(false));
	*(*(grid + 4) + 7) = Square(4, 7, new King(false));
	*(*(grid + 5) + 7) = Square(5, 7, new Bishop(false));
	*(*(grid + 6) + 7) = Square(6, 7, new Knight(false));
	*(*(grid + 7) + 7) = Square(7, 7, new Rook(false));


	for (int x = 0; x < 8; x++) {
		*(*(grid + x) + 1) = Square(x, 1, new Pawn(true));
	}

	for (int x = 0; x < 8; x++) {
		*(*(grid + x) + 6) = Square(x, 6, new Pawn(false));
	}

	for (int y = 2; y < 6; y++) {
		for (int x = 0; x < 8; x++) {
			*(*(grid + x) + y) = Square(x, y, NULL);
		}
	}
}
