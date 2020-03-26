#pragma once
#include<iostream>

enum PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };

class Piece {
 public:
  Piece(bool white);
  void setWhite(bool white);
  bool isWhite();
  void setKilled(bool killed);
  bool isKilled();
  void setFirstMoved();
  bool isFirstMove();
  virtual PieceType getPieceType() = 0;
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY) = 0;
  bool isPotentialKillSameColor(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece);
 private:
  bool killed = false;
  bool white = false;
  bool firstMove = true;
};

class King : public Piece {
 public:
  King(bool white);
  virtual PieceType getPieceType();
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::KING;
};

class Queen : public Piece {
 public:
  Queen(bool white);
  virtual PieceType getPieceType();
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::QUEEN;
};

class Bishop : public Piece {
 public:
  Bishop(bool white);
  virtual PieceType getPieceType();
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::BISHOP;
};

class Knight : public Piece {
 public:
  Knight(bool white);
  virtual PieceType getPieceType();
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::KNIGHT;
};

class Rook : public Piece {
 public:
  Rook(bool white);
  virtual PieceType getPieceType();
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::ROOK;
};

class Pawn : public Piece {
 public:
  Pawn(bool white);
  virtual PieceType getPieceType();
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int sourceX, int sourceY,
                       int killedX, int killedY);
 private:
  PieceType pieceType = PieceType::PAWN;
};


class PieceFactory {
 public:
   std::shared_ptr<Piece> Create(bool white, PieceType pieceType) {
    switch (pieceType)
    {
    case PieceType::KING:
      return std::shared_ptr<Piece>(new King(white));
    case PieceType::QUEEN:
      return std::shared_ptr<Piece>(new Queen(white));
    case PieceType::BISHOP:
      return std::shared_ptr<Piece>(new Bishop(white));
    case PieceType::KNIGHT:
      return std::shared_ptr<Piece>(new Knight(white));
    case PieceType::ROOK:
      return std::shared_ptr<Piece>(new Rook(white));
    case PieceType::PAWN:
      return std::shared_ptr<Piece>(new Pawn(white));
    default:
      throw std::invalid_argument("Wrong piece type received.");
    }
  }
};