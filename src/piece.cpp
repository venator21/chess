#include"piece.h"


Piece::Piece(bool white) {
  this->setWhite(white);
}
void Piece::setWhite(bool white) {
  this->white = white;
}
bool Piece::isWhite() {
  return this->white;
}
void Piece::setKilled(bool killed) {
  this->killed = killed;
}
bool Piece::isKilled() {
  return this->killed;
}
void Piece::setFirstMoved() {
  this->firstMove = false;
}
bool Piece::isFirstMove() {
  return this->firstMove;
}

bool Piece::isPotentialKillSameColor(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece) {
  if (killedPiece != nullptr) {
    if (sourcePiece->isWhite() == killedPiece->isWhite())
      return true;
    else
      return false;
  }
  return false;
}


King::King(bool white)
  : Piece{ white } {
}
PieceType King::getPieceType() {
  return this->pieceType;
}
bool King::canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                   int sourceX, int sourceY,
                   int killedX, int killedY) {

  if (isPotentialKillSameColor(sourcePiece, killedPiece))
    return false;

  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  if (x > 1)
    return false;

  if (y > 1)
    return false;

  if (x + y <= 2)
    return true;
  else
    return false;
}


Queen::Queen(bool white)
  : Piece{ white } {
}
PieceType Queen::getPieceType() {
  return this->pieceType;
}
bool Queen::canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                    int sourceX, int sourceY,
                    int killedX, int killedY) {
  if (isPotentialKillSameColor(sourcePiece, killedPiece))
    return false;

  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  if ((x == 0 || y == 0) || (x == y))
    return true;
  else
    return false;
}


Bishop::Bishop(bool white)
  : Piece{ white } {
}
PieceType Bishop::getPieceType() {
  return this->pieceType;
}
bool Bishop::canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                     int sourceX, int sourceY,
                     int killedX, int killedY) {
  if (isPotentialKillSameColor(sourcePiece, killedPiece))
    return false;

  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  if (x == y) return true;
  return false;
}


Knight::Knight(bool white)
  : Piece{ white } {
}
PieceType Knight::getPieceType() {
  return this->pieceType;
}
bool Knight::canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                     int sourceX, int sourceY,
                     int killedX, int killedY) {
  if (isPotentialKillSameColor(sourcePiece, killedPiece))
    return false;

  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  if ((x == 1 && y == 2) || (x == 2 && y == 1))
    return true;
  else
    return false;
}


Rook::Rook(bool white)
  : Piece{ white } {
}
PieceType Rook::getPieceType() {
  return this->pieceType;
}
bool Rook::canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                   int sourceX, int sourceY,
                   int killedX, int killedY) {
  if (isPotentialKillSameColor(sourcePiece, killedPiece))
    return false;

  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  if (x == 0 || y == 0)
    return true;
  else
    return false;
}


Pawn::Pawn(bool white)
  : Piece{ white } {
}
PieceType Pawn::getPieceType() {
  return this->pieceType;
}
bool Pawn::canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                   int sourceX, int sourceY,
                   int killedX, int killedY) {
  if (isPotentialKillSameColor(sourcePiece, killedPiece))
    return false;

  int* x;
  int* y;

  if (sourcePiece->isWhite())
  {
    x = new int(killedX - sourceX);
    y = new int(killedY - sourceY);
  }
  else
  {
    x = new int(sourceX - killedX);
    y = new int(sourceY - killedY);
  }

  if ((killedPiece == nullptr && *x == 0 && //can move vertical without kill
      (*y == 1 || *y == 2 && this->isFirstMove() == true)) || //can move vertical 1 sq or 2 sq if first move
      (killedPiece != nullptr && abs(*x) == 1 && *y == 1)) { //can move 1 sq diagonal if going for a kill
    delete x;
    delete y;
    return true;
  }
  else {
    delete x;
    delete y;
    return false;
  }
}