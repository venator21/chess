#pragma once
#include"player.h"
#include"square.h"


class Move {
private:
	Player player;
	Square* start;
	Square* end;
	Piece* pieceMoved;
	Piece* pieceKilled; //TODO what to do with this
	bool castlingMove = false;

public:
	Move(Player player, Square* start, Square* end);
	bool isCastlingMove();
	void setCastlingMove(bool castlingMove);
	Square* getStart();
	Square* getEnd();


};
