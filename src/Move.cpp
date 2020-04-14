#include"Move.h"

Move::Move(Player player, int sourceX, int sourceY,
                          int destinationX, int destinationY,
                          std::shared_ptr<Piece> pieceMoved,
                          std::shared_ptr<Piece> pieceKilled) {
  this->player = player;
  this->sourceX = sourceX;
  this->sourceY = sourceY;
  this->destinationX = destinationX;
  this->destinationY = destinationY;
  this->pieceMoved = pieceMoved;
  this->pieceKilled = pieceKilled;
}

int  Move::getMovedPieceX() {
  return this->sourceX;
}

int  Move::getMovedPieceY() {
  return this->sourceY;
}

int  Move::getKilledPieceX() {
  return this->destinationX;
}

int  Move::getKilledPieceY() {
  return this->destinationY;
}

std::shared_ptr<Piece>  Move::getMovedPiece() {
  return this->pieceMoved;
}

std::shared_ptr<Piece>  Move::getKilledPiece() {
  return this->pieceKilled;
}