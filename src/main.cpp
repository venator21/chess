#include <iostream>
#include"game.h"

using namespace std;

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


int main() {
	string move;
	int startX;
	int startY;
	int endX;
	int endY;
	GameStatus gameStatus = GameStatus::ACTIVE;
	Game game;

	game.printBoard();
	while (gameStatus == GameStatus::ACTIVE) {
		string turn = (game.getCurrentTurn().isWhiteSide() ? "WHITE's" : "BLACK's");
		cout << turn << " turn: ";
		cin >> move;

		startX = transformMoveInput(move[0])-1;
		startY = (int)move[1]-48-1;
		endX = transformMoveInput(move[3])-1;
		endY = (int)move[4]-48-1;

		if (game.playerMove(game.getCurrentTurn(), startX, startY, endX, endY) == false) {
			cout << "wrong move! try again." << endl;
			continue;
		}
		cout << endl;
		game.printBoard();
	}
	//cout << EndGameStatus << endl;

}
//Square* getSquare(int x, int y, Square** grid) {
//	return (*(grid + x) + y);
//}
//
//int main() {
//
//	Square** grid = new Square * [8];
//	for (int i = 0; i < 8; ++i) {
//		grid[i] = new Square[8];
//	}
//	*(*(grid + 0) + 0) = Square(0, 0, new Rook(true));
//	*(*(grid + 1) + 0) = Square(1, 0, new Knight(true));
//
//	getSquare(0, 0, grid)->getPiece();
//	getSquare(0, 0, grid)->setPiece(getSquare(1, 0, grid)->getPiece());
//	getSquare(0, 0, grid)->getPiece();
//
//}