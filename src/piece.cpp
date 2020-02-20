#include"piece.h"
#include<iostream>

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
bool King::canMove() { //TODO add args and logic for returning true or false
	return 0;
}




Queen::Queen(bool white)
	: Piece{ white } {
}
bool Queen::canMove() { //TODO add args and logic for returning true or false
	return 0;
}



Bishop::Bishop(bool white)
	: Piece{ white } {
}
	bool Bishop::canMove() { //TODO add args and logic for returning true or false
	return 0;
}


Knight::Knight(bool white)
	: Piece{ white } {
}
bool Knight::canMove() { //TODO add args and logic for returning true or false
	return 0;
}


Rook::Rook(bool white)
	: Piece{ white } {
}
bool Rook::canMove() { //TODO add args and logic for returning true or false
	return 0;
}


Pawn::Pawn(bool white)
	: Piece{ white } {
}
void Pawn::getPromoted() { //TODO implementation of promotion
}
bool Pawn::canMove() { //TODO add args and logic for returning true or false
	return 0;
}
bool Pawn::isValidEnPassant() {  //TODO add arguments
	return 0; //TODO Logic for returning true or false 
}
bool Pawn::isValidPromotion() {  //TODO add arguments
	return 0; //TODO Logic for returning true or false 
}