#pragma once

#include<iostream>
#include"Piece.h"
#include"Player.h"

class Move {
public:
    Move(bool whiteSide, int sourceX, int sourceY, int destinationX, int destinationY,
         std::shared_ptr<Piece> pieceMoved, std::shared_ptr<Piece> pieceKilled);

    int getMovedPieceX() const;

    int getMovedPieceY() const;

    int getKilledPieceX() const;

    int getKilledPieceY() const;

    std::shared_ptr<Piece> getMovedPiece() const;

    std::shared_ptr<Piece> getKilledPiece() const;

private:
    bool whiteSide;
    int sourceX;
    int sourceY;
    int destinationX;
    int destinationY;
    std::shared_ptr<Piece> pieceMoved;
    std::shared_ptr<Piece> pieceKilled;
};