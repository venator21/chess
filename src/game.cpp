#include"game.h"

Game::Game() {
	this->player1 = HumanPlayer(true);
	this->player2 = HumanPlayer(false);
	this->initializeGame(player1, player2);
}

void Game::initializeGame(Player player1, Player player2) {
	board.initializeBoard();

	if (player1.isWhiteSide()) {
		this->currentTurn = player1;
	}
	else {
		this->currentTurn = player2;
	}

	movesPlayed.clear();
	
}

Player Game::getCurrentTurn() {
	return this->currentTurn;
}

bool Game::playerMove(Player player, int startX,
	int startY, int endX, int endY)
{
	Square* startSquare = board.getSquare(startX, startY);
	Square* endSquare = board.getSquare(endX, endY);
	Move move = Move(player, startSquare, endSquare);
	return this->makeMove(move, player);
}

bool Game::makeMove(Move move, Player player)
{
	Piece* sourcePiece = move.getStart()->getPiece();
	Piece* killedPiece = move.getEnd()->getPiece();

	if (sourcePiece == NULL) {
		return false;
	}

	/* valid player 
	if (player != currentTurn) {
		return false;
	}*/

	if (sourcePiece->isWhite() != player.isWhiteSide()) {
		return false;
	}

	// valid move? 
	if (!sourcePiece->canMove(sourcePiece, killedPiece, 
							move.getStart()->getX(), move.getStart()->getY(), 
							move.getEnd()->getX(), move.getEnd()->getY())){ // TODO
		return false;
	}

	// kill? 

	if (killedPiece != NULL) {
		killedPiece->setKilled(true);
	}

	// castling? 
	/*
	if (sourcePiece != null && sourcePiece instanceof King
		&& sourcePiece.isCastlingMove()) {
		move.setCastlingMove(true);
	}*/

	// store the move 
	movesPlayed.push_back(move);

	// move piece from the stat box to end box 
	move.getEnd()->setPiece(move.getStart()->getPiece());
	move.getStart()->setPiece(NULL);

	if (killedPiece != NULL && killedPiece->getPieceType() == PieceType::KING) {
		if (player.isWhiteSide()) {
			this->gameStatus = GameStatus::WHITE_WINS;
		}
		else {
			this->gameStatus = GameStatus::BLACK_WINS;
		}
	}

	// set the current turn to the other player 
	if (this->currentTurn.isWhiteSide() == true) {
		this->currentTurn = player2;
	}
	else {
		this->currentTurn = player1;
	}

	return true;
}

void Game::printBoard() {
	using namespace std;


	//cout << "y:" << endl;
	for (int i = 7; i >= 0; i--)
	{
		cout << " " << i + 1 << "|";
		for (int j = 0; j < 8; j++)
		{
			Piece* p = board.getSquare(j, i)->getPiece();

			if (p == NULL) {
				cout << " " << "\1" << " ";
				continue;
			}

			switch (p->getPieceType())
			{
			case PieceType::KING: (p->isWhite() == true) ? cout << " K " : cout << " k ";
				break;
			case PieceType::QUEEN: (p->isWhite() == true) ? cout << " Q " : cout << " q ";
				break;
			case PieceType::BISHOP:(p->isWhite() == true) ? cout << " B " : cout << " b ";
				break;
			case PieceType::KNIGHT:(p->isWhite() == true) ? cout << " H " : cout << " h ";
				break;
			case PieceType::ROOK: (p->isWhite() == true) ? cout << " R " : cout << " r ";
				break;
			case PieceType::PAWN: (p->isWhite() == true) ? cout << " P " : cout << " p ";
				break;
			}

		}
		cout << endl;

	}
	cout << "   _______________________" << endl;
	cout << "    A  B  C  D  E  F  G  H " << endl;

}


