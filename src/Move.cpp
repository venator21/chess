#include"Move.h"

Move::Move(const Player &player, int sourceX, int sourceY, int destinationX, int destinationY,
           const std::shared_ptr<Piece> &pieceMoved, const std::shared_ptr<Piece> &pieceKilled) :
        player(player),
        sourceX(sourceX),
        sourceY(sourceY),
        destinationX(destinationX),
        destinationY(destinationY),
        pieceMoved(pieceMoved),
        pieceKilled(pieceKilled) {}

int  Move::getMovedPieceX() const {
  return this->sourceX;
}

int  Move::getMovedPieceY() const {
  return this->sourceY;
}

int  Move::getKilledPieceX() const {
  return this->destinationX;
}

int  Move::getKilledPieceY() const {
  return this->destinationY;
}

std::shared_ptr<Piece>  Move::getMovedPiece() const {
  return this->pieceMoved;
}

std::shared_ptr<Piece>  Move::getKilledPiece() const {
  return this->pieceKilled;
}


