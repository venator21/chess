#pragma once
#include"piece.h"

class Square {
public:
  Square();
  Square(int x, int y, std::shared_ptr<Piece> piece, bool promotion);
  void setPiece(std::shared_ptr<Piece> piece);
  std::shared_ptr<Piece> getPiece();
  void setX(int x);
  int getX();
  void setY(int y);
  int getY();
  bool getPromotion();

private:
  int x;
  int y;
  std::shared_ptr<Piece> piece;
  bool promotion;
};