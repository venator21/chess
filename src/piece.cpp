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
};
bool King::isValidCastling(){  //TODO add arguments

	if (this->isCastlingDone()) {
		return false;
	}
	return 0;//TODO Logic for returning true or false 
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
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if (x + y <= 2) return true;
}




Queen::Queen(bool white)
	: Piece{ white } {
}
PieceType Queen::getPieceType() {
	return this->pieceType;
};
bool Queen::canMove(Piece* sourcePiece, Piece* killedPiece,
					int sourceX, int sourceY,
					int killedX, int killedY) { //TODO add args and logic for returning true or false
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if ((x == 0 || y == 0) || (x == y)) return true;
}



Bishop::Bishop(bool white)
	: Piece{ white } {
}
PieceType Bishop::getPieceType() {
	return this->pieceType;
};
	bool Bishop::canMove(Piece* sourcePiece, Piece* killedPiece,
						int sourceX, int sourceY,
						int killedX, int killedY) { //TODO add args and logic for returning true or false
		int x = abs(sourceX - killedX);
		int y = abs(sourceY - killedY);
		if (x == y) return true;
}


Knight::Knight(bool white)
	: Piece{ white } {
}
PieceType Knight::getPieceType() {
	return this->pieceType;
};
bool Knight::canMove(Piece* sourcePiece, Piece* killedPiece,
					int sourceX, int sourceY,
					int killedX, int killedY) { //TODO add args and logic for returning true or false
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if ((x == 1 && y == 2) || (x == 2 && y == 1)) return true;
}


Rook::Rook(bool white)
	: Piece{ white } {
}
PieceType Rook::getPieceType() {
	return this->pieceType;
};
bool Rook::canMove(Piece* sourcePiece, Piece* killedPiece,
					int sourceX, int sourceY,
					int killedX, int killedY) { //TODO add args and logic for returning true or false
	int x = abs(sourceX - killedX);
	int y = abs(sourceY - killedY);
	if (x == 0 || y == 0) return true;
}


Pawn::Pawn(bool white)
	: Piece{ white } {
}
PieceType Pawn::getPieceType() {
	return this->pieceType;
};
void Pawn::getPromoted() { //TODO implementation of promotion
}
bool Pawn::canMove(Piece* sourcePiece, Piece* killedPiece,
					int sourceX, int sourceY,
					int killedX, int killedY) { //TODO add args and logic for returning true or false
	return 1;
}
bool Pawn::isValidEnPassant() {  //TODO add arguments
	return 0; //TODO Logic for returning true or false 
}
bool Pawn::isValidPromotion() {  //TODO add arguments
	return 0; //TODO Logic for returning true or false 
}