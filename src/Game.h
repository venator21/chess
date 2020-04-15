#pragma once
#include"Board.h"

enum class GameStatus { ACTIVE, BLACK_WINS, WHITE_WINS, DRAW };

class Game {
 public:
  Game();
  bool playGameTurn(std::string const& inputMove);
  Player getcurrentPlayer() const;
  GameStatus getGameStatus() const;
  static std::vector<int> transformMoveInputToCoord(std::string const& string);
  static int charTransformation(char const& s);
  void printGame();

 private:
  Board board;
  HumanPlayer wPlayer{true};
  HumanPlayer bPlayer{false};
  Player* currentPlayer;
  GameStatus gameStatus{GameStatus::ACTIVE};
};