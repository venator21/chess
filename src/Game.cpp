#include"Game.h"


Game::Game() {
  this->currentPlayer = &wPlayer;
  this->board.initializeBoard();
}

bool Game::playGameTurn(std::string const& inputMove) {
  std::vector<int> start = transformMoveInputToCoord(inputMove.substr(0, 2));
  std::vector<int> end = transformMoveInputToCoord(inputMove.substr(3, 2));

  if (!board.makeMove(currentPlayer, start[0], start[1], end[0], end[1]))
    return false;

  if (board.isKingKilled()) {
    if (currentPlayer->isWhiteSide())
      this->gameStatus = GameStatus::WHITE_WINS;
    else
      this->gameStatus = GameStatus::BLACK_WINS;
  }

  if (currentPlayer->isWhiteSide())
    this->currentPlayer = &bPlayer;
  else
    this->currentPlayer = &wPlayer;
}

Player Game::getcurrentPlayer() const {
  return this->currentPlayer;
}

GameStatus Game::getGameStatus() const {
  return this->gameStatus;
}

std::vector<int> Game::transformMoveInputToCoord(std::string const& string) {
  int x = static_cast<int>(charTransformation(string[0]) - 1);
  int y = static_cast<int>(string[1] - 48 - 1);
  std::vector<int> coord { x, y };
  return coord;
}

int Game::charTransformation(char const& s) {
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