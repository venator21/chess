#pragma once
#include<iostream>
#include"board.h"
#include"move.h"
#include"piece.h"
#include <list>

enum class GameStatus { ACTIVE, BLACK_WINS, WHITE_WINS, DRAW };

class Game {
 public:
	Game();
	void initializeGame(Player player1, Player player2);
	Player getCurrentTurn();
	bool playerMove(Player player, int startX, int startY, int endX, int endY);
	bool makeMove(Move move, Player player);
	void printBoard();
  GameStatus getGameStatus();
  bool isEnPassant();
  std::list<int> EnPassantTarget();

 private:
  Player player1;
  Player player2;
  Board board;
  Player currentTurn;
  GameStatus gameStatus;
  std::list<Move> movesPlayed;
};