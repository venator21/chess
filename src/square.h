#pragma once

class Piece;

class Square {
private:
	int x;
	int y;
	Piece* piece;


public:
	Square();
	Square(int x, int y, Piece* piece);

	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	void setPiece(Piece* piece);
	Piece* getPiece();
};

