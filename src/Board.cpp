#include"Board.h"

Board::Board() {
  this->initializeBoard();
}

void Board::initializeBoard() {
  this->initializeGrid();
  this->initializePieces();
}

void Board::initializeGrid() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      // check if square need promotion flag = true
      if (y < 1 || y > 6)
        grid[x][y] = Square(x, y, nullptr, true);
      else
        grid[x][y] = Square(x, y, nullptr, false);
    }
  }
}

void Board::initializePieces() {
  grid[0][0].setPiece(pieceFactory.create(WHITE, ROOK));
  grid[1][0].setPiece(pieceFactory.create(WHITE, KNIGHT));
  grid[2][0].setPiece(pieceFactory.create(WHITE, BISHOP));
  grid[3][0].setPiece(pieceFactory.create(WHITE, QUEEN));
  grid[4][0].setPiece(pieceFactory.create(WHITE, KING));
  grid[5][0].setPiece(pieceFactory.create(WHITE, BISHOP));
  grid[6][0].setPiece(pieceFactory.create(WHITE, KNIGHT));
  grid[7][0].setPiece(pieceFactory.create(WHITE, ROOK));

  grid[0][7].setPiece(pieceFactory.create(BLACK, ROOK));
  grid[1][7].setPiece(pieceFactory.create(BLACK, KNIGHT));
  grid[2][7].setPiece(pieceFactory.create(BLACK, BISHOP));
  grid[3][7].setPiece(pieceFactory.create(BLACK, QUEEN));
  grid[4][7].setPiece(pieceFactory.create(BLACK, KING));
  grid[5][7].setPiece(pieceFactory.create(BLACK, BISHOP));
  grid[6][7].setPiece(pieceFactory.create(BLACK, KNIGHT));
  grid[7][7].setPiece(pieceFactory.create(BLACK, ROOK));

  for (int x = 0; x < 8; x++) {
    grid[x][1].setPiece(pieceFactory.create(WHITE, PAWN));
  }

  for (int x = 0; x < 8; x++) {
    grid[x][6].setPiece(pieceFactory.create(BLACK, PAWN));
  }
}

Square Board::getSquare(int const& x, int const& y) const {
  return grid[x][y];
}

bool Board::makeMove(Player currentPlayer, int const& sourceX, int const& sourceY,
                                         int const& destinationX, int const& destinationY) {
  std::shared_ptr<Piece> sourcePiece = getSquare(sourceX, sourceY).getPiece();
  std::shared_ptr<Piece> killedPiece = getSquare(destinationX, destinationY).getPiece();

  // is there a source piece to move? 
  if (sourcePiece == nullptr)
    return false;

  // valid movement board-wise? (checked first due to castling conflict if otherwise)
  if (sourcePiece->getPieceType() != PieceType::KNIGHT)
    if (!isMovementPathClear(sourceX, sourceY, destinationX, destinationY))
      return false;

  // valid movement piece-wise? (checked second due to castling conflict if otherwise)
  if (isValidCastling(sourceX, sourceY, destinationX, destinationY))
    executeCastlingMove(sourceX, sourceY, destinationX, destinationY);
  else if (isEnPassant(sourceX, sourceY, destinationX, destinationY))
    executeEnPassantMove();
  else if (!sourcePiece->canMove(sourcePiece, killedPiece, sourceX, sourceY, destinationX, destinationY))
    return false;

  // first movement of piece instance? 
  if (sourcePiece->isFirstMove())
    sourcePiece->setFirstMoved();

  // promotion?
  if (sourcePiece->getPieceType() == PieceType::PAWN && getSquare(destinationX, destinationY).isPromotionSquare())
    executePromotion(currentPlayer, destinationX, destinationY);

  // kill? 
  if (killedPiece != nullptr)
    killedPiece->setKilled(true);

  sourcePieceMoved(sourceX, sourceY, destinationX, destinationY);
  movesPlayed.emplace_back(currentPlayer, sourceX, sourceY, destinationX, destinationY, sourcePiece, killedPiece);

  return true;
}


void Board::sourcePieceMoved(int const& sourceX, int const& sourceY,
                      int const& destinationX, int const& destinationY) {
  grid[destinationX][destinationY].setPiece(getSquare(sourceX, sourceY).getPiece());
  grid[sourceX][sourceY].setPiece(nullptr);
}



bool Board::isMovementPathClear(int const& sourceX, int const& sourceY,
                                int const& destinationX, int const& destinationY) const {
  int x = abs(sourceX - destinationX);
  int y = abs(sourceY - destinationY);
  int maxRange;
  int minRange;

  //vertical movement
  if (x == 0) {
    if (sourceY > destinationY) {
      maxRange = sourceY;
      minRange = destinationY;
    }
    else {
      maxRange = destinationY;
      minRange = sourceY;
    }
    for (int i = minRange + 1; i < maxRange; i++) {
      if (getSquare(destinationX, i).getPiece() != nullptr)
        return false;
    }
  }

  //horizontal movement
  if (y == 0) {
    if (sourceX > destinationX) {
      maxRange = sourceX;
      minRange = destinationX;
    }
    else {
      maxRange = destinationX;
      minRange = sourceX;
    }
    for (int i = minRange + 1; i < maxRange; i++) {
      if (getSquare(i, destinationY).getPiece() != nullptr)
        return false;
    }
  }

  //diagonal movement
  if (x == y) {
    //north east
    if (sourceX < destinationX && sourceY < destinationY) {
      for (int i = sourceX + 1, j = sourceY + 1; i < destinationX || j < destinationY; i++, j++) {
        if (getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
    //south east
    if (sourceX < destinationX && sourceY > destinationY) {
      for (int i = sourceX + 1, j = sourceY - 1; i < destinationX || j > destinationY; i++, j--) {
        if (getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
    //south west
    if (sourceX > destinationX && sourceY > destinationY) {
      for (int i = sourceX - 1, j = sourceY - 1; i < destinationX || j > destinationY; i--, j--) {
        if (getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
    //north west
    if (sourceX > destinationX && sourceY < destinationY) {
      for (int i = sourceX - 1, j = sourceY + 1; i < destinationX || j < destinationY; i--, j++) {
        if (getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
  }
  return true;
}

void Board::executePromotion(Player currentPlayer, int const& destinationX, int const& destinationY) {
  int promotionPiece = 0;
  while (promotionPiece < 1 || promotionPiece > 4) {
    std::cout << "\nChose promotion piece (QUEEN - 1 , BISHOP -2, KNIGHT - 3, ROOK - 4): ";
    std::cin >> promotionPiece;
  }
  switch (promotionPiece) {
  case 1:
    grid[destinationX][destinationY].setPiece(pieceFactory.create(currentPlayer.isWhiteSide(), QUEEN));
  case 2:
    grid[destinationX][destinationY].setPiece(pieceFactory.create(currentPlayer.isWhiteSide(), BISHOP));
  case 3:
    grid[destinationX][destinationY].setPiece(pieceFactory.create(currentPlayer.isWhiteSide(), KNIGHT));
  case 4:
    grid[destinationX][destinationY].setPiece(pieceFactory.create(currentPlayer.isWhiteSide(), ROOK));
  default:
    throw std::string("Wrong promotion input!");
  }
}

bool Board::isValidCastling(int const& sourceX, int const& sourceY, int const& destinationX, int const& destinationY) const {
  int xDiff = sourceX - destinationX;
  int yDiff = sourceY - destinationY;
  int rookX;
  int rookY = sourceY;

  if (getSquare(sourceX, sourceY).getPiece()->getPieceType() != PieceType::KING)
    return false;

  if (getSquare(destinationX, destinationY).getPiece() != nullptr)
    return false;

  if (!getSquare(sourceX, sourceY).getPiece()->isFirstMove())
    return false;

  // while castling king movement is horizontal
  if (yDiff != 0) 
    return false;

  // while castling king destination can only result in two specific squares
  if (!(xDiff == 2 || xDiff == -2)) 
    return false;

  // X-wise - check which rook is participating, Y already derived from King position
  if (xDiff == 2)
    rookX = 0;
  else if (xDiff == -2)
    rookX = 7;

  if (getSquare(rookX, rookY).getPiece() == nullptr)
    return false;

  if (!getSquare(rookX, rookY).getPiece()->isFirstMove())
    return false;

  int minRange{};
  int maxRange{};

  if (rookX == 0) {
    minRange = 0;
    maxRange = 4;
  }
  else if (rookX == 7) {
    minRange = 4;
    maxRange = 7;
  }

  // check if path between king and rook is clear
  for (int i = minRange + 1; i < maxRange; i++) {
    if (getSquare(i, rookY).getPiece() != nullptr)
      return false;
  }
  return true;
}

void Board::executeCastlingMove(int const& sourceX, int const& sourceY, int const& destinationX, int const& destinationY) {
  // if true move rook to the proper position
  if (destinationX == 6) {
    grid[5][destinationY].setPiece(getSquare(7, destinationY).getPiece());
    grid[7][destinationY].setPiece(nullptr);
  }
  else if (destinationX == 2) {
    grid[3][destinationY].setPiece(getSquare(0, destinationY).getPiece());
    grid[0][destinationY].setPiece(nullptr);
  }
}

bool Board::isEnPassant(int const& sourceX, int const& sourceY,
  int const& destinationX, int const& destinationY) {
  // ignore if it is first move of the game
  if (movesPlayed.empty())
    return false;

  Move lastMove = movesPlayed.back();

  if (lastMove.getMovedPiece()->getPieceType() != PieceType::PAWN)
    return false;

  int yDiff = lastMove.getKilledPieceY() - lastMove.getMovedPieceY();

  // since pawn can only move forward, can determine if it is white or black
  // based on vertical difference value
  if (!(yDiff == 2 && lastMove.getMovedPiece()->isWhite() == true ||
    yDiff == -2 && lastMove.getMovedPiece()->isWhite() == false))
    return false;

  // check if moved piece is pawn and destination square is on targeted enPassant
  auto [targetX, targetY] = EnPassantTarget();
  if (!(getSquare(sourceX, sourceY).getPiece()->getPieceType() == PieceType::PAWN &&
    destinationX == targetX && destinationY == targetY))
    return false;

  return true;
}

void Board::executeEnPassantMove() {
  int x = movesPlayed.back().getKilledPieceX();
  int y = movesPlayed.back().getKilledPieceY();
  grid[x][y].setPiece(nullptr);
}

std::tuple<int, int> Board::EnPassantTarget() const {
  if (movesPlayed.empty()) {
    std::tuple<int, int> target = { -1, -1 };
    return target;
  }

  Move lastMove = this->movesPlayed.back();
  int yDiff = lastMove.getKilledPieceY() - lastMove.getMovedPieceY();

  // determine valid destination of en passant based on vertical movement of previous move 
  if (yDiff == 2) {
    std::tuple<int, int> target = { lastMove.getKilledPieceX(), lastMove.getKilledPieceY() - 1 };
    return target;
  }
  else if (yDiff == -2) {
    std::tuple<int, int> target = { lastMove.getKilledPieceX(), lastMove.getKilledPieceY() + 1 };
    return target;
  }
  else {
    std::tuple<int, int> target = { -1, -1 };
    return target;
  }
}

bool Board::isKingKilled() const {
  Move lastMove = movesPlayed.back();

  if (lastMove.getKilledPiece() == nullptr)
    return false;

  if (lastMove.getKilledPiece()->getPieceType() == PieceType::KING)
    return true;
  else
    return false;
}

void Board::printBoard() const {

  for (int i = 7; i >= 0; i--) {
    std::cout << " " << i + 1 << "|";
    for (int j = 0; j < 8; j++) {
      auto p = getSquare(j, i).getPiece();
      if (p == nullptr) {
        std::cout << " " << "." << " ";
        continue;
      }
      switch (p->getPieceType()) {
      case PieceType::KING: p->isWhite() ? std::cout << " K " : std::cout << " k ";
        break;
      case PieceType::QUEEN: p->isWhite() ? std::cout << " Q " : std::cout << " q ";
        break;
      case PieceType::BISHOP: p->isWhite() ? std::cout << " B " : std::cout << " b ";
        break;
      case PieceType::KNIGHT: p->isWhite() ? std::cout << " N " : std::cout << " n ";
        break;
      case PieceType::ROOK: p->isWhite() ? std::cout << " R " : std::cout << " r ";
        break;
      case PieceType::PAWN: p->isWhite() ? std::cout << " P " : std::cout << " p ";
        break;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "   _______________________" << std::endl;
  std::cout << "    A  B  C  D  E  F  G  H " << std::endl;
}