#include"board.h"

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
      if (x < 1 || x > 6)
        grid[x][y] = Square(x, y, nullptr, true);
      else
        grid[x][y] = Square(x, y, nullptr, false);
    }
  }
}

void Board::initializePieces() {
  grid[0][0].setPiece(pieceFactory.Create(WHITE, ROOK));
  grid[1][0].setPiece(pieceFactory.Create(WHITE, KNIGHT));
  grid[2][0].setPiece(pieceFactory.Create(WHITE, BISHOP));
  grid[3][0].setPiece(pieceFactory.Create(WHITE, QUEEN));
  grid[4][0].setPiece(pieceFactory.Create(WHITE, KING));
  grid[5][0].setPiece(pieceFactory.Create(WHITE, BISHOP));
  grid[6][0].setPiece(pieceFactory.Create(WHITE, KNIGHT));
  grid[7][0].setPiece(pieceFactory.Create(WHITE, ROOK));

  grid[0][7].setPiece(pieceFactory.Create(BLACK, ROOK));
  grid[1][7].setPiece(pieceFactory.Create(BLACK, KNIGHT));
  grid[2][7].setPiece(pieceFactory.Create(BLACK, BISHOP));
  grid[3][7].setPiece(pieceFactory.Create(BLACK, QUEEN));
  grid[4][7].setPiece(pieceFactory.Create(BLACK, KING));
  grid[5][7].setPiece(pieceFactory.Create(BLACK, BISHOP));
  grid[6][7].setPiece(pieceFactory.Create(BLACK, KNIGHT));
  grid[7][7].setPiece(pieceFactory.Create(BLACK, ROOK));

  for (int x = 0; x < 8; x++) {
    grid[x][1].setPiece(pieceFactory.Create(WHITE, PAWN));
  }

  for (int x = 0; x < 8; x++) {
    grid[x][6].setPiece(pieceFactory.Create(BLACK, PAWN));
  }
}

Square Board::getSquare(int x, int y) {
  return grid[x][y];
}

bool Board::isMovementPathClear(Board board,
  int sourceX, int sourceY,
  int killedX, int killedY) {
  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  int* maxRange;
  int* minRange; //TODO zrobic zaiast ptr jakies referencje

  //vertical movement
  if (x == 0) {
    if (sourceY > killedY) {
      maxRange = &sourceY;
      minRange = &killedY;
    }
    else {
      maxRange = &killedY;
      minRange = &sourceY;
    }
    for (int i = *minRange + 1; i < *maxRange; i++) {
      if (board.getSquare(killedX, i).getPiece() != nullptr)
        return false;
    }
  }

  //horizontal movement
  if (y == 0) {
    if (sourceX > killedX) {
      maxRange = &sourceX;
      minRange = &killedX;
    }
    else {
      maxRange = &killedX;
      minRange = &sourceX;
    }
    for (int i = *minRange + 1; i < *maxRange; i++) {
      if (board.getSquare(i, killedY).getPiece() != nullptr)
        return false;
    }
  }

  //diagonal movement
  if (x == y) {
    //north east
    if (sourceX < killedX && sourceY < killedY) {
      for (int i = sourceX + 1, j = sourceY + 1; i < killedX || j < killedY; i++, j++) {
        if (board.getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
    //south east
    if (sourceX < killedX && sourceY > killedY) {
      for (int i = sourceX + 1, j = sourceY - 1; i < killedX || j > killedY; i++, j--) {
        if (board.getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
    //south west
    if (sourceX > killedX&& sourceY > killedY) {
      for (int i = sourceX - 1, j = sourceY - 1; i < killedX || j > killedY; i--, j--) {
        if (board.getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
    //north west
    if (sourceX > killedX&& sourceY < killedY) {
      for (int i = sourceX - 1, j = sourceY + 1; i < killedX || j < killedY; i--, j++) {
        if (board.getSquare(i, j).getPiece() != nullptr)
          return false;
      }
    }
  }
  return true;
}

bool Board::isValidCastling(Board board, Square startSquare, Square endSquare) {
  int xDiff = startSquare.getX() - endSquare.getX();
  int yDiff = startSquare.getY() - endSquare.getY();
  int* rookX = new int;
  int rookY = startSquare.getY();

  if (startSquare.getPiece()->getPieceType() != PieceType::KING)
    return false;

  if (startSquare.getPiece()->isFirstMove() != true)
    return false;

  //while castling king movement is horizontal
  if (yDiff != 0) 
    return false;

  //while castling king destination can only result in two specific squares
  if (!(xDiff == 2 || xDiff == -2)) 
    return false;

  // X-wise - check which rook is participating, Y already derived from King position
  if (xDiff == 2)
    *rookX = 0;
  else if (xDiff == -2)
    *rookX = 7;

  if (board.getSquare(*rookX, rookY).getPiece()->isFirstMove() == false) {
    delete rookX;
    return false;
  }

  int* minRange = new int;
  int* maxRange = new int;

  if (*rookX == 0) {
    *minRange = 0;
    *maxRange = 4;
  }
  else if (*rookX == 7) {
    *minRange = 4;
    *maxRange = 7;
  }

  //check if path between king and rook is clear
  for (int i = *minRange + 1; i < *maxRange; i++) {
    if (board.getSquare(i, rookY).getPiece() != nullptr) {
      delete rookX;
      delete minRange;
      delete maxRange;
      return false;
    }
  }

  delete rookX;
  delete minRange;
  delete maxRange;

  return true;
}