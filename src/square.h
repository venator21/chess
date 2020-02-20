#pragma once
#include"piece.h"

class Square {
private:
	int x;
	int y;
	Piece* piece;

public:
	Square(int x, int y, Piece* piece);
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	void setPiece(Piece* piece);
	Piece* getPiece();
};

