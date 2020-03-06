#pragma once
#include"piece.h"

class Square {
 public:
	Square();
	Square(int x, int y, Piece* piece);
  void setPiece(Piece* piece);
  Piece* getPiece();
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();

 private:
  int x;
  int y;
  Piece* piece;
};