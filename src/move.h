#pragma once
#include<iostream>
#include"Piece.h"
#include"Player.h"

class Move {
 public:
  Move(Player player, int sourceX, int sourceY, 
                      int destinationX, int destinationY,
                      std::shared_ptr<Piece> pieceMoved,
                      std::shared_ptr<Piece> pieceKilled);
  int getMovedPieceX();
  int getMovedPieceY();
  int getKilledPieceX();
  int getKilledPieceY();
  std::shared_ptr<Piece> getMovedPiece();
  std::shared_ptr<Piece> getKilledPiece();



 private:
  Player player;
  int sourceX;
  int sourceY;
  int destinationX;
  int destinationY;
  std::shared_ptr<Piece> pieceMoved;
  std::shared_ptr<Piece> pieceKilled;
};