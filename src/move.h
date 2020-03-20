#pragma once
#include"player.h"
#include"square.h"

class Move {
 public:
  Move(Player player, Square* start, Square* end);
  Square* getStart();
  Square* getEnd();
  bool isCastlingMove();
  void setCastlingMove(bool castlingMove);

 private:
  Player player;
  Square* start;
  Square* end;
  Piece* pieceMoved;
  Piece* pieceKilled;
  bool castlingMove = false;
};