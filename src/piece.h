#pragma once

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

	virtual bool canMove() = 0; //TODO add arguments
};

class King : public Piece {
private:
	bool castlingDone = false;
	bool isValidCastling();

public:
	King(bool white);

	bool isCastlingDone();
	void setCastlingDone(bool castlingDone);

	virtual bool canMove(); //TODO add args and logic for returning true or false
};


class Queen : public Piece {
public:
	Queen(bool white);

	virtual bool canMove(); //TODO add args and logic for returning true or false

};

class Bishop : public Piece {
public:
	Bishop(bool white);
	virtual bool canMove(); //TODO add args and logic for returning true or false

};

class Knight : public Piece {
public:
	Knight(bool white);
	virtual bool canMove(); //TODO add args and logic for returning true or false

};

class Rook : public Piece {
public:
	Rook(bool white);
	virtual bool canMove(); //TODO add args and logic for returning true or false
};

class Pawn : public Piece {
private:
	bool isValidEnPassant();  //TODO add arguments
	bool isValidPromotion();  //TODO add arguments

public:
	Pawn(bool white);

	void getPromoted(); //TODO implementation of promotion

	virtual bool canMove(); //TODO add args and logic for returning true or false

};