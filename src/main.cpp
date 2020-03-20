#include<iostream>
#include<stdlib.h>
#include"game.h"

using namespace std;

int transformMoveInput(char s);

int main() {
  string move;
  int startX;
  int startY;
  int endX;
  int endY;
  Game game;

  game.printBoard();
  while (game.getGameStatus() == GameStatus::ACTIVE) {
    string turn = (game.getCurrentTurn().isWhiteSide() ? "WHITE's" : "BLACK's");
    cout << turn << " turn: ";
    cin >> move;

    //input move tranformation from e.g. A1-A2 into int X and Y
    startX = transformMoveInput(move[0]) - 1;
    startY = (int)move[1] - 48 - 1;
    endX = transformMoveInput(move[3]) - 1;
    endY = (int)move[4] - 48 - 1;

    if (game.playerMove(game.getCurrentTurn(), startX, startY, endX, endY) == false) {
      cout << "wrong move! try again." << endl;
      continue;
    }

    system("CLS");
    game.printBoard();

    if (game.getGameStatus() == GameStatus::BLACK_WINS) {
      cout << "BLACK_WINS" << endl;
    }
    else if (game.getGameStatus() == GameStatus::WHITE_WINS) {
      cout << "WHITE_WINS" << endl;
    }
    else if (game.getGameStatus() == GameStatus::DRAW) {
      cout << "DRAW" << endl;
    }
  }
};

int transformMoveInput(char s) {
  switch (s)
  {
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
  }
}