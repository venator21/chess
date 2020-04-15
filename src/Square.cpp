#include"Square.h"

Square::Square(int x, int y, std::shared_ptr<Piece> piece, bool promotionSquare) :
                x(x), y(y), piece(piece), promotionSquare(promotionSquare) {}

void Square::setPiece(std::shared_ptr<Piece> piece) {
  this->piece = piece;
}

std::shared_ptr<Piece> Square::getPiece() const {
  return this->piece;
}

void Square::setX(int x) {
  this->x = x;
}

int Square::getX() const {
  return this->x;
}

void Square::setY(int y) {
  this->y = y;
}

int Square::getY() const {
  return this->y;
}

bool Square::isPromotionSquare() const {
  return this->promotionSquare;
}