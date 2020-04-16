#pragma once

#include<iostream>
#include<vector>
#include<array>
#include <list>
#include<string>
#include"Square.h"
#include"Piece.h"
#include"Player.h"
#include"Move.h"

enum Color {
    BLACK = 0, WHITE = 1
};

template<class T, size_t ROW, size_t COL>
using Matrix = std::array<std::array<T, COL>, ROW>;


class Board {
public:
    Board();

    void initializeBoard();

    void initializeGrid();

    void initializePieces();

    Square getSquare(int const &x, int const &y) const;

    bool makeMove(Player *const currentPlayer, int const &sourceX, int const &sourceY, int const &killedX,
                  int const &killedY);

    void sourcePieceMoved(int const &sourceX, int const &sourceY, int const &destinationX, int const &destinationY);

    bool isMovementPathClear(int const &sourceX, int const &sourceY, int const &killedX, int const &killedY) const;

    void executePromotion(Player* const currentPlayer, int const &destinationX, int const &destinationY);

    bool
    isValidCastling(int const &sourceX, int const &sourceY, int const &destinationX, int const &destinationY) const;

    void executeCastlingMove(int const &sourceX, int const &sourceY, int const &destinationX, int const &destinationY);

    bool isEnPassant(int const &sourceX, int const &sourceY, int const &destinationX, int const &destinationY);

    void executeEnPassantMove();

    std::vector<int> EnPassantTarget() const;

    bool isKingKilled() const;

    void printBoard() const;

    Matrix<Square, 8, 8> grid;
    std::list<Move> movesPlayed;
};


