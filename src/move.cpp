#include"piece.h"
#include"square.h"
#include"player.h"

class Move {
private:
	Player player;
	Square start;
	Square end;
	Piece* pieceMoved;
	Piece* pieceKilled; //TODO what to do with this
	bool castlingMove = false;

public:
	Move(Player player, Square start, Square end) {
		this->player = player;
		this->start = start;
		this->end = end;
		this->pieceMoved = start.getPiece();
	}

	bool isCastlingMove() {
		return this->castlingMove == true;
	}

	void setCastlingMove(bool castlingMove)
	{
		this->castlingMove = castlingMove;
	}
};
