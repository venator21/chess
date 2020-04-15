#pragma once
#include<memory>
#include<stdexcept>

enum PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };

class Piece {
 public:
  Piece(bool white);
  void setWhite(bool color);
  bool isWhite() const;
  void setKilled(bool kill);
  void setFirstMoved();
  bool isFirstMove() const;
  virtual PieceType getPieceType() const = 0;
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const = 0;
  bool isPotentialKillSameColor(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece) const;

 private:
  bool killed = false;
  bool white = false;
  bool firstMove = true;
};

class King : public Piece {
 public:
  King(bool white);
  bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const override;
  PieceType getPieceType() const override;
 private:
  PieceType pieceType = PieceType::KING;
};

class Queen : public Piece {
 public:
  Queen(bool white);
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const override;
  PieceType getPieceType() const override;
 private:
  PieceType pieceType = PieceType::QUEEN;
};

class Bishop : public Piece {
 public:
  Bishop(bool white);
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const override;
  PieceType getPieceType() const override;
 private:
  PieceType pieceType = PieceType::BISHOP;
};

class Knight : public Piece {
 public:
  Knight(bool white);
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const override;
  PieceType getPieceType() const override;
 private:
  PieceType pieceType = PieceType::KNIGHT;
};

class Rook : public Piece {
 public:
  Rook(bool white);
  virtual bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const override;
    PieceType getPieceType() const override;
 private:
  PieceType pieceType = PieceType::ROOK;
};

class Pawn : public Piece {
 public:
  Pawn(bool white);
  bool canMove(std::shared_ptr<Piece> sourcePiece, std::shared_ptr<Piece> killedPiece,
                       int const& sourceX, int const& sourceY,
                       int const& killedX, int const& killedY) const override;
    PieceType getPieceType() const override;
 private:
  PieceType pieceType = PieceType::PAWN;
};


class PieceFactory {
 public:
   std::shared_ptr<Piece> create(bool white, PieceType pieceType) {
    switch (pieceType) {
    case PieceType::KING:
      return std::shared_ptr<Piece>(std::make_shared<King>(white));
    case PieceType::QUEEN:
      return std::shared_ptr<Piece>(std::make_shared<Queen>(white));
    case PieceType::BISHOP:
      return std::shared_ptr<Piece>(std::make_shared<Bishop>(white));
    case PieceType::KNIGHT:
      return std::shared_ptr<Piece>(std::make_shared<Knight>(white));
    case PieceType::ROOK:
      return std::shared_ptr<Piece>(std::make_shared<Rook>(white));
    case PieceType::PAWN:
      return std::shared_ptr<Piece>(std::make_shared<Pawn>(white));
    default:
      throw std::invalid_argument("Wrong piece type received.");
    }
  }
};