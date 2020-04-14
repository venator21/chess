#include<iostream>
#include<string>
#include"Game.h"

int main() {
  std::string move;
  Game game;
  game.printGame();
  while (game.getGameStatus() == GameStatus::ACTIVE) {

    std::string turn = (game.getcurrentPlayer().isWhiteSide() ? "WHITE's" : "BLACK's");
    std::cout << turn << " turn: ";
    std::cin >> move;


    if (game.playGameTurn(move) == false) {
      std::cout << "wrong move! try again." << std::endl;
      continue;
    }

    system("CLS");
    game.printGame();

    if (game.getGameStatus() == GameStatus::BLACK_WINS)
      std::cout << "BLACK_WINS" << std::endl;
    else if (game.getGameStatus() == GameStatus::WHITE_WINS)
      std::cout << "WHITE_WINS" << std::endl;
    else if (game.getGameStatus() == GameStatus::DRAW)
      std::cout << "DRAW" << std::endl;
  }
};