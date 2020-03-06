#include<iostream>
#include<cstdlib>
#include"piece.h"

using namespace std;

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


King::King(bool white)
	: Piece{ white } {
}
PieceType King::getPieceType() {
  return this->pieceType;
}
bool King::isCastlingDone() {
	return this->castlingDone == true;
}
void King::setCastlingDone(bool castlingDone) {
	this->castlingDone = castlingDone;
}
bool King::canMove(Piece* sourcePiece, Piece* killedPiece, 
					         int sourceX, int sourceY,
					         int killedX, int killedY) {
	if (killedPiece != NULL) {
		if (sourcePiece->isWhite() == killedPiece->isWhite()) {
			return false;
		}
	}
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if (x + y <= 2)
		return true;
	else
		return false;
}
bool King::isValidCastling() {  //TODO add arguments
  if (this->isCastlingDone()) {
    return false;
  }
  return 0;//TODO Logic for returning true or false 
}


Queen::Queen(bool white)
	: Piece{ white } {
}
PieceType Queen::getPieceType() {
	return this->pieceType;
}
bool Queen::canMove(Piece* sourcePiece, Piece* killedPiece, 
					          int sourceX, int sourceY,
					          int killedX, int killedY) {
	if (killedPiece != NULL) {
		if (sourcePiece->isWhite() == killedPiece->isWhite()) {
			return false;
		}
	}
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
bool Bishop::canMove(Piece* sourcePiece, Piece* killedPiece, 
					           int sourceX, int sourceY,
					           int killedX, int killedY) {
	if (killedPiece != NULL) {
		if (sourcePiece->isWhite() == killedPiece->isWhite()) {
			return false;
		}
	}
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if (x == y) return true;
	return 1;
}


Knight::Knight(bool white)
	: Piece{ white } {
}
PieceType Knight::getPieceType() {
	return this->pieceType;
}
bool Knight::canMove(Piece* sourcePiece, Piece* killedPiece, 
					           int sourceX, int sourceY,
					           int killedX, int killedY) {
	if (killedPiece != NULL) {
		if (sourcePiece->isWhite() == killedPiece->isWhite()) {
			return false;
		}
	}
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
bool Rook::canMove(Piece* sourcePiece, Piece* killedPiece, 
					         int sourceX, int sourceY,
					         int killedX, int killedY) {
	if (killedPiece != NULL) {
		if (sourcePiece->isWhite() == killedPiece->isWhite()) {
			return false;
		}
	}
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if (x == 0 || y == 0) 
		return true;
	else
		return false;
}


Pawn::Pawn(bool white)
	: Piece{ white } {
  this->firstMove = true;
}
PieceType Pawn::getPieceType() {
	return this->pieceType;
};
bool Pawn::canMove(Piece* sourcePiece, Piece* killedPiece, 
					         int sourceX, int sourceY,
					         int killedX, int killedY) {
	if (killedPiece != NULL) {
		if (sourcePiece->isWhite() == killedPiece->isWhite()) {
			return false;
		}
	}

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

	if ((killedPiece == NULL && *x == 0 && (*y == 1 || *y == 2 && this->firstMove == true)) || (killedPiece != NULL && abs(*x) == 1 && *y == 1)) {
		delete x;
		delete y;
    this->firstMove = false;
		return true;
	}
	else {
		delete x;
		delete y;
    this->firstMove = false;
		return false;
	}

}
bool Pawn::isValidEnPassant() {  //TODO add arguments
	return 0; //TODO Logic for returning true or false 
}