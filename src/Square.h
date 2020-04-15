#pragma once
#include"Piece.h"

class Square {
public:
  Square()=default;
  Square(int x, int y, std::shared_ptr<Piece> piece, bool promotion);
  void setPiece(std::shared_ptr<Piece> piece);
  std::shared_ptr<Piece> getPiece() const;
  void setX(int x);
  int getX() const;
  void setY(int y);
  int getY() const;
  bool isPromotionSquare() const;

private:
  int x;
  int y;
  std::shared_ptr<Piece> piece;
  bool promotionSquare;
};