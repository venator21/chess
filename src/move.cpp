#include"move.h"

Move::Move(Player player, Square* start, Square* end) {
  this->player = player;
  this->start = start;
  this->end = end;
  this->pieceMoved = start->getPiece();
  this->pieceKilled = end->getPiece();
}

Square* Move::getStart() {
  return this->start;
}

Square* Move::getEnd() {
  return this->end;
}