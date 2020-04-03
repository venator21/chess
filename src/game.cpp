#include"game.h"

Game::Game() {
  this->gameStatus = GameStatus::ACTIVE;
  this->w_player = static_cast<Player>(HumanPlayer(true));
  this->b_player = static_cast<Player>(HumanPlayer(false));
  this->currentPlayer = w_player;
  this->board.initializeBoard();
}

bool Game::playGameTurn(std::string inputMove) {
  std::vector<int> start = transformMoveInputToCoord(inputMove.substr(0, 2));
  std::vector<int> end = transformMoveInputToCoord(inputMove.substr(3, 2));

  if (!board.makeMove(currentPlayer, start[0], start[1], end[0], end[1]))
    return false;

  if (board.isKingKilled()) {
    bool white = currentPlayer.isWhiteSide();
    if (white)
      this->gameStatus = GameStatus::WHITE_WINS;
    else
      this->gameStatus = GameStatus::BLACK_WINS;
  }

  if (currentPlayer.isWhiteSide())
    this->currentPlayer = b_player;
  else
    this->currentPlayer = w_player;
}

Player Game::getcurrentPlayer() {
  return this->currentPlayer;
}

GameStatus Game::getGameStatus() {
  return this->gameStatus;
}

std::vector<int> Game::transformMoveInputToCoord(std::string string) {
  int x = static_cast<int>(charTransformation(string[0]) - 1);
  int y = static_cast<int>(string[1] - 48 - 1);
  std::vector<int> coord { x, y };
  return coord;
}

int Game::charTransformation(char s) {
  switch (s) {
  case 'A':
    return 1;
  case 'B':
    return 2;
  case 'C':
    return 3;
  case 'D':
    return 4;
  case 'E':
    return 5;
  case 'F':
    return 6;
  case 'G':
    return 7;
  case 'H':
    return 8;
  default:
    throw std::invalid_argument("Wrong input received.");
  }
};

void Game::printGame() {
  board.printBoard();
}