#include<iostream>
#include"board.h"

Board::Board() {
	this->initializeBoard();
}

void Board::initializeBoard() {
	for (int i = 0; i < 8; ++i) {
		grid[i] = new Square[8];
	}

	*(*(grid + 0) + 0) = Square(0, 0, new Rook(true), true);
	*(*(grid + 1) + 0) = Square(1, 0, new Knight(true), true);
	*(*(grid + 2) + 0) = Square(2, 0, new Bishop(true), true);
	*(*(grid + 3) + 0) = Square(3, 0, new Queen(true), true);
	*(*(grid + 4) + 0) = Square(4, 0, new King(true), true);
	*(*(grid + 5) + 0) = Square(5, 0, new Bishop(true), true);
	*(*(grid + 6) + 0) = Square(6, 0, new Knight(true), true);
	*(*(grid + 7) + 0) = Square(7, 0, new Rook(true), true);

	*(*(grid + 0) + 7) = Square(0, 7, new Rook(false), true);
	*(*(grid + 1) + 7) = Square(1, 7, new Knight(false), true);
	*(*(grid + 2) + 7) = Square(2, 7, new Bishop(false), true);
	*(*(grid + 3) + 7) = Square(3, 7, new Queen(false), true);
	*(*(grid + 4) + 7) = Square(4, 7, new King(false), true);
	*(*(grid + 5) + 7) = Square(5, 7, new Bishop(false), true);
	*(*(grid + 6) + 7) = Square(6, 7, new Knight(false), true);
	*(*(grid + 7) + 7) = Square(7, 7, new Rook(false), true);


	for (int x = 0; x < 8; x++) {
		*(*(grid + x) + 1) = Square(x, 1, new Pawn(true), false);
	}

	for (int x = 0; x < 8; x++) {
		*(*(grid + x) + 6) = Square(x, 6, new Pawn(false), false);
	}

	for (int y = 2; y < 6; y++) {
		for (int x = 0; x < 8; x++) {
			*(*(grid + x) + y) = Square(x, y, NULL, false);
		}
	}
}

Square* Board::getSquare(int x, int y) {
  return (*(grid + x) + y);
}

bool Board::isMovementPathClear(Board board,
                                int sourceX, int sourceY,
                                int killedX, int killedY) {
  int x = abs(sourceX - killedX);
  int y = abs(sourceY - killedY);
  int* maxRange;
  int* minRange;
  int* maxX;
  int* minX;
  int* maxY;
  int* minY;
  if (x == 0)
  {
    if (sourceY > killedY)
    {
      maxRange = &sourceY;
      minRange = &killedY;
    }
    else
    {
      maxRange = &killedY;
      minRange = &sourceY;
    }
    for (int i = *minRange + 1; i < *maxRange; i++)
    {
      if (board.getSquare(killedX, i)->getPiece() != NULL)
        return false;
    }
  }
  if (y == 0)
  {
	  if (sourceX > killedX)
	  {
		  maxRange = &sourceX;
		  minRange = &killedX;
	  }
	  else
	  {
		  maxRange = &killedX;
		  minRange = &sourceX;
	  }
	  for (int i = *minRange + 1; i < *maxRange; i++)
	  {
		  if (board.getSquare(i, i)->getPiece() != NULL)
			  return false;
	  }
  }
  if (x == y)
  {
		if (sourceX > killedX)
		{
			maxX = &sourceX;
			minX = &killedX;
		}
		else
		{
			maxX = &killedX;
			minX = &sourceX;
		}
		if (sourceY > killedY)
		{
			maxY = &sourceY;
			minY = &killedY;
		}
		else
		{
			maxY = &killedY;
			minY = &sourceY;
		}
		for (int i = *minX + 1, j = *minY + 1; i < *maxX || j < *maxY; i++, j++)
		{
			if (board.getSquare(i, j)->getPiece() != NULL)
				return false;
		}
	}
  return true;
 }

bool Board::isValidCastling(Board board, Square* startSquare, Square* endSquare) {
  int xDiff = startSquare->getX() - endSquare->getX();
  int yDiff = startSquare->getY() - endSquare->getY();
  int* rookX = new int;
  int rookY = startSquare->getY();

  if (startSquare->getPiece()->getPieceType() != PieceType::KING)
    return false;

  if (startSquare->getPiece()->isFirstMove() != true)
  {
    return false;
  }
  if (yDiff != 0)
  {
    return false;
  }
  if (!(xDiff == 2 || xDiff == -2))
  {
    return false;
  }

  if (xDiff == 2)
  {
    *rookX = 0;
  }
  else if (xDiff == -2)
  {
    *rookX = 7;
  }

  if (board.getSquare(*rookX, rookY)->getPiece()->isFirstMove() == false)
  {
    delete rookX;
    return false;
  }

  int* minRange = new int;
  int* maxRange = new int;

  if (*rookX == 0)
  {
    *minRange = 0;
    *maxRange = 4;
  }
  else if (*rookX == 7)
  {
    *minRange = 4;
    *maxRange = 7;
  }
  for (int i = *minRange + 1; i < *maxRange; i++)
  {
    if (board.getSquare(i, rookY)->getPiece() != NULL)
    {
      delete rookX;
      delete minRange;
      delete maxRange;
      return false;
    }
  }

  delete rookX;
  delete minRange;
  delete maxRange;

  return true;//TODO Logic for returning true or false 
}