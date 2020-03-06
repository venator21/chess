#pragma once

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};

class Piece {
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
 private:
	bool killed = false;
	bool white = false;
};

class King : public Piece {
 public:
  King(bool white);
  bool isCastlingDone();
  void setCastlingDone(bool castlingDone);
  virtual PieceType getPieceType();
  virtual bool canMove(Piece* sourcePiece, Piece* killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
	PieceType pieceType = PieceType::KING;
	bool castlingDone = false;
	bool isValidCastling();  //TODO
};

class Queen : public Piece {
 public:
	Queen(bool white);
  virtual PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					             int sourceX, int sourceY,
					             int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::QUEEN;
};

class Bishop : public Piece {
 public:
	Bishop(bool white);
  virtual PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					             int sourceX, int sourceY,
					             int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::BISHOP;
};

class Knight : public Piece {
 public:
	Knight(bool white);
	virtual PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					             int sourceX, int sourceY,
					             int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::KNIGHT;
};

class Rook : public Piece {
 public:
	Rook(bool white);
  virtual PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					             int sourceX, int sourceY,
					             int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::ROOK;
};

class Pawn : public Piece {
 public:
	Pawn(bool white);
  virtual PieceType getPieceType();
	virtual bool canMove(Piece* sourcePiece, Piece* killedPiece, 
					             int sourceX, int sourceY,
					             int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::PAWN;
  bool firstMove;
  bool isValidEnPassant();  //TODO add arguments
};