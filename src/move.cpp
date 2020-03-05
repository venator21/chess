#include"move.h"

Move::Move(Player player, Square* start, Square* end) {
	this->player = player;
	this->start = start;
	this->end = end;
	this->pieceMoved = start->getPiece();
	this->pieceKilled = end->getPiece();
}

bool Move::isCastlingMove() {
	return this->castlingMove == true;
}

void Move::setCastlingMove(bool castlingMove)
{
	this->castlingMove = castlingMove;
}

Square* Move::getStart(){
	return this->start;
}

Square* Move::getEnd() {
	return this->end;
}



