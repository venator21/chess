#pragma once
#include"board.h"

enum class GameStatus { ACTIVE, BLACK_WINS, WHITE_WINS, DRAW };

class Game {
 public:
  Game();
  bool playGameTurn(std::string inputMove);
  Player getcurrentPlayer();
  GameStatus getGameStatus();
  std::vector<int> transformMoveInputToCoord(std::string string);
  int charTransformation(char s);
  void printGame();

 private:
  Board board;
  Player w_player;
  Player b_player;
  Player currentPlayer;
  GameStatus gameStatus;
};