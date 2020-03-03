#pragma once
#include"board.h"

enum PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};

class Piece {
private:
	bool killed = false;
	bool white = false;

public:
	Piece(bool white);

	void setWhite(bool white);
	bool isWhite();
	void setKilled(bool killed);
	bool isKilled();
	virtual PieceType getPieceType() = 0;
	virtual bool canMove(Board board) = 0;
};

class King : public Piece {
private:
	PieceType pieceType = KING;
	bool castlingDone = false;
	bool isValidCastling();

public:
	King(bool white);

	PieceType getPieceType();
	bool isCastlingDone();
	void setCastlingDone(bool castlingDone);

	virtual bool canMove(Board board); //TODO add args and logic for returning true or false
};


class Queen : public Piece {
private:
	PieceType pieceType = QUEEN;
public:
	Queen(bool white);
	PieceType getPieceType();
	virtual bool canMove(Board board);

};

class Bishop : public Piece {
private:
	PieceType pieceType = BISHOP;
public:
	Bishop(bool white);
	PieceType getPieceType();
	virtual bool canMove(Board board);

};

class Knight : public Piece {
private:
	PieceType pieceType = KNIGHT;
public:
	Knight(bool white);
	PieceType getPieceType();
	virtual bool canMove(Board board);

};

class Rook : public Piece {
private:
	PieceType pieceType = ROOK;
public:
	Rook(bool white);
	PieceType getPieceType();
	virtual bool canMove(Board board);
};

class Pawn : public Piece {
private:
	PieceType pieceType = PAWN;
	bool isValidEnPassant();  //TODO add arguments
	bool isValidPromotion();  //TODO add arguments

public:
	Pawn(bool white);
	PieceType getPieceType();
	void getPromoted(); //TODO implementation of promotion

	virtual bool canMove(Board board);

};