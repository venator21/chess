#pragma once


enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};

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
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY) = 0;
};

class King : public Piece {
private:
	PieceType pieceType = PieceType::KING;
	bool castlingDone = false;
	bool isValidCastling();

public:
	King(bool white);

	PieceType getPieceType();
	bool isCastlingDone();
	void setCastlingDone(bool castlingDone);

	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY); //TODO add args and logic for returning true or false
};


class Queen : public Piece {
private:
	PieceType pieceType = PieceType::QUEEN;
public:
	Queen(bool white);
	PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY);

};

class Bishop : public Piece {
private:
	PieceType pieceType = PieceType::BISHOP;
public:
	Bishop(bool white);
	PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY);

};

class Knight : public Piece {
private:
	PieceType pieceType = PieceType::KNIGHT;
public:
	Knight(bool white);
	PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY);

};

class Rook : public Piece {
private:
	PieceType pieceType = PieceType::ROOK;
public:
	Rook(bool white);
	PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY);
};

class Pawn : public Piece {
private:
	PieceType pieceType = PieceType::PAWN;
	bool isValidEnPassant();  //TODO add arguments
	bool isValidPromotion();  //TODO add arguments

public:
	Pawn(bool white);
	PieceType getPieceType();
	void getPromoted(); //TODO implementation of promotion

	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					int sourceX, int sourceY,
					int killedX, int killedY);

};