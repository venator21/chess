#include"square.h"

Square::Square() {
	this->setX(x);
	this->setY(y);
	this->setPiece(piece);
  this->promotion = promotion;
}

Square::Square(int x, int y, Piece* piece, bool promotion) {
	this->setX(x);
	this->setY(y);
	this->setPiece(piece);
  this->promotion = promotion;
}

void Square::setPiece(Piece* piece) {
  this->piece = piece;
}

Piece* Square::getPiece() {
  return this->piece;
}

void Square::setX(int x) {
	this->x = x;
}

int Square::getX() {
	return this->x;
}

void Square::setY(int y) {
	this->y = y;
}

int Square::getY() {
	return this->y;
}

bool Square::getPromotion() {
  return this->promotion;
}