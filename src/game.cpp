#include"game.h"

Game::Game() {
  this->gameStatus = GameStatus::ACTIVE;
  this->player1 = HumanPlayer(true);
  this->player2 = HumanPlayer(false);
  this->initializeGame(player1, player2);
}

void Game::initializeGame(Player player1, Player player2) {
  board.initializeBoard();

  if (player1.isWhiteSide())
    this->currentTurn = player1;
  else
    this->currentTurn = player2;

  movesPlayed.clear();
}

Player Game::getCurrentTurn() {
  return this->currentTurn;
};

bool Game::playerMove(Player player, int startX,
                      int startY, int endX, int endY) {
  Square startSquare = board.getSquare(startX, startY);
  Square endSquare = board.getSquare(endX, endY);
  Move move = Move(player, startSquare, endSquare);

  return this->makeMove(move, player);
};

bool Game::makeMove(Move move, Player player) {
  std::shared_ptr<Piece> sourcePiece = move.getStart().getPiece();
  std::shared_ptr<Piece> killedPiece = move.getEnd().getPiece();

  // is there a source piece to move? 
  if (sourcePiece == nullptr)
    return false;

  // does source piece belong to the player?
  if (sourcePiece->isWhite() != player.isWhiteSide())
    return false;

  // initializing variables in case of castling or en passant
  bool isCastling = board.isValidCastling(board, move.getStart(), move.getEnd());
  std::vector<int> enPassantTarget = this->EnPassantTarget();

	// valid piece movement? //TODO zmienic to, wyglada dziwnie
  if (isCastling) {}
  else if (this->isEnPassant() && 
           sourcePiece->getPieceType() == PieceType::PAWN &&
           move.getEnd().getX() == enPassantTarget[0] && 
           move.getEnd().getY() == enPassantTarget[1]) {}
  else {
    if (!sourcePiece->canMove(sourcePiece, killedPiece,
                              move.getStart().getX(), move.getStart().getY(),
                              move.getEnd().getX(), move.getEnd().getY()))
      return false;
  }

  // valid board movement? 
  if (sourcePiece->getPieceType() != PieceType::KNIGHT) {
    if (!board.isMovementPathClear(board,
                                   move.getStart().getX(), move.getStart().getY(),
                                   move.getEnd().getX(), move.getEnd().getY()))
      return false;
  }

  // kill? 
  if (killedPiece != nullptr)
    killedPiece->setKilled(true);


  // is casteling valid and being played?
  if (board.isValidCastling(board, move.getStart(), move.getEnd())) {
    //if true move rook to the proper position
    if (move.getEnd().getX() == 6) {
      board.getSquare(5, move.getEnd().getY()).setPiece(board.getSquare(7, move.getEnd().getY()).getPiece());
      board.getSquare(7, move.getEnd().getY()).setPiece(nullptr);
    }
    else if (move.getEnd().getX() == 2) {
      board.getSquare(3, move.getEnd().getY()).setPiece(board.getSquare(0, move.getEnd().getY()).getPiece());
      board.getSquare(0, move.getEnd().getY()).setPiece(nullptr);
    }
  }

  // is enPassant valid and being played? //TODO slabo to wyglada
  if (this->isEnPassant() && sourcePiece->getPieceType() == PieceType::PAWN &&
    move.getEnd().getX() == enPassantTarget[0] && move.getEnd().getY() == enPassantTarget[1]) {

    movesPlayed.back().getEnd().setPiece(nullptr);
  };

  // move source piece from the start square to end square 
  move.getEnd().setPiece(move.getStart().getPiece());
  move.getStart().setPiece(nullptr);

  // first movement of piece instance? 
  if (sourcePiece->isFirstMove() == true)
    sourcePiece->setFirstMoved();

  // promotion?
  if (sourcePiece->getPieceType() == PieceType::PAWN && move.getEnd().getPromotion() == true) {
    int promotionPiece = 0;
    while (promotionPiece < 1 || promotionPiece > 4) {
      std::cout << "\nChose promotion piece (QUEEN - 1 , BISHOP -2, KNIGHT - 3, ROOK - 4): ";
      std::cin >> promotionPiece;
    }
    //delete move.getEnd().getPiece();
    if (promotionPiece == 1)
      move.getEnd().setPiece(pieceFactory.Create(currentTurn.isWhiteSide(), QUEEN));
    else if (promotionPiece == 2)
      move.getEnd().setPiece(pieceFactory.Create(currentTurn.isWhiteSide(), BISHOP));
    else if (promotionPiece == 3)
      move.getEnd().setPiece(pieceFactory.Create(currentTurn.isWhiteSide(), KNIGHT));
    else if (promotionPiece == 4)
      move.getEnd().setPiece(pieceFactory.Create(currentTurn.isWhiteSide(), ROOK));
  }

  // store the move 
  movesPlayed.push_back(move);

  // check win condition
  if (killedPiece != nullptr && killedPiece->getPieceType() == PieceType::KING) {
    if (player.isWhiteSide())
      this->gameStatus = GameStatus::WHITE_WINS;
    else
      this->gameStatus = GameStatus::BLACK_WINS;
  };

  // set the current turn to the other player 
  if (this->currentTurn.isWhiteSide() == true)
    this->currentTurn = player2;
  else
    this->currentTurn = player1;

  return true;
}

void Game::printBoard() {

  for (int i = 7; i >= 0; i--) {
    std::cout << " " << i + 1 << "|";
    for (int j = 0; j < 8; j++) {
      std::shared_ptr<Piece> p = board.getSquare(j, i).getPiece();
      if (p == nullptr) {
        std::cout << " " << "\1" << " ";
        continue;
      }
      switch (p->getPieceType()) {
      case PieceType::KING: (p->isWhite() == true) ? std::cout << " K " : std::cout << " k ";
        break;
      case PieceType::QUEEN: (p->isWhite() == true) ? std::cout << " Q " : std::cout << " q ";
        break;
      case PieceType::BISHOP:(p->isWhite() == true) ? std::cout << " B " : std::cout << " b ";
        break;
      case PieceType::KNIGHT:(p->isWhite() == true) ? std::cout << " N " : std::cout << " n ";
        break;
      case PieceType::ROOK: (p->isWhite() == true) ? std::cout << " R " : std::cout << " r ";
        break;
      case PieceType::PAWN: (p->isWhite() == true) ? std::cout << " P " : std::cout << " p ";
        break;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "   _______________________" << std::endl;
  std::cout << "    A  B  C  D  E  F  G  H " << std::endl;
}

GameStatus Game::getGameStatus() {
  return this->gameStatus;
};

bool Game::isEnPassant() {
  //ignore if it is first move of the game
  if (this->movesPlayed.size() == 0)
    return false;

  Move lastMove = this->movesPlayed.back();

  if (lastMove.getEnd().getPiece()->getPieceType() != PieceType::PAWN)
    return false;

  int yDiff = lastMove.getEnd().getY() - lastMove.getStart().getY();

  //since pawn can only move forward, can determine if it is white or black
  //based on vertical difference value
  if (!(yDiff == 2 && lastMove.getEnd().getPiece()->isWhite() == true ||
    yDiff == -2 && lastMove.getEnd().getPiece()->isWhite() == false))
    return false;

  return true;
}

std::vector<int> Game::EnPassantTarget() {

  if (this->movesPlayed.size() == 0) {
    std::vector<int> target = { -1, -1 };
    return target;
  }

  Move lastMove = this->movesPlayed.back();
  int yDiff = lastMove.getEnd().getY() - lastMove.getStart().getY();

  //determine valid destination of en passant based on vertical movement of previous move 
  if (yDiff == 2) {
    std::vector<int> target = { lastMove.getEnd().getX(), lastMove.getEnd().getY() - 1 };
    return target;
  }
  else if (yDiff == -2) {
    std::vector<int> target = { lastMove.getEnd().getX(), lastMove.getEnd().getY() + 1 };
    return target;
  }
  else {
    std::vector<int> target = { -1, -1 };
    return target;
  }
}