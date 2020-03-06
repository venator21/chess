#include"game.h"

using namespace std;

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

  // is there a source piece to move? 
	if (sourcePiece == NULL) {
		return false;
	}

  // does source piece belong to the player?
	if (sourcePiece->isWhite() != player.isWhiteSide()) {
		return false;
	}

	// valid piece movement? 
	if (!sourcePiece->canMove(sourcePiece, killedPiece, 
							              move.getStart()->getX(), move.getStart()->getY(), 
							              move.getEnd()->getX(), move.getEnd()->getY())){
		return false;
	}

  // valid board movement? 
  if (sourcePiece->getPieceType() != PieceType::KNIGHT)
  {
    if (!board.isMovementPathClear(board,
                                   move.getStart()->getX(), move.getStart()->getY(),
                                   move.getEnd()->getX(), move.getEnd()->getY())) {
      return false;
    }
  }

	// kill? 
	if (killedPiece != NULL) {
		killedPiece->setKilled(true);
	}

	// store the move 
	movesPlayed.push_back(move);

	// move piece from the start square to end square 
	move.getEnd()->setPiece(move.getStart()->getPiece());
	move.getStart()->setPiece(NULL);

  // promotion?
  if (sourcePiece->getPieceType() == PieceType::PAWN && move.getEnd()->getPromotion() == true)
  {
    int promotionPiece = 0;
    while (promotionPiece < 1 || promotionPiece > 4)
    {
      cout << "\nChose promotion piece (QUEEN - 1 , BISHOP -2, KNIGHT - 3, ROOK - 4): ";
      cin >> promotionPiece;
    }
    delete move.getEnd()->getPiece();
    if (promotionPiece == 1)
    {
      move.getEnd()->setPiece(new Queen(currentTurn.isWhiteSide()));
    }
    else if (promotionPiece == 2)
    {
      move.getEnd()->setPiece(new Bishop(currentTurn.isWhiteSide()));
    }
    else if (promotionPiece == 3)
    {
      move.getEnd()->setPiece(new Knight(currentTurn.isWhiteSide()));
    }
    else if (promotionPiece == 4)
    {
      move.getEnd()->setPiece(new Rook(currentTurn.isWhiteSide()));
    }
  }

  // check win condition
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

	for (int i = 7; i >= 0; i--)
	{
		cout << " " << i + 1 << "|";
		for (int j = 0; j < 8; j++)
		{
			Piece* p = board.getSquare(j, i)->getPiece();
			if (p == NULL) {
				cout << " " << " " << " ";
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
			case PieceType::KNIGHT:(p->isWhite() == true) ? cout << " N " : cout << " n ";
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


