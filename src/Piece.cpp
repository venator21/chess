#include"Piece.h"

Piece::Piece(bool white) {
    this->setWhite(white);
}

void Piece::setWhite(bool color) {
    this->white = color;
}

bool Piece::isWhite() const {
    return this->white;
}

void Piece::setKilled(bool kill) {
    this->killed = kill;
}

void Piece::setFirstMoved() {
    this->firstMove = false;
}

bool Piece::isFirstMove() const {
    return this->firstMove;
}

bool
Piece::isPotentialKillSameColor(const std::shared_ptr <Piece> &sourcePiece,
                                const std::shared_ptr <Piece> &killedPiece) {
    if (killedPiece != nullptr) {
        return sourcePiece->isWhite() == killedPiece->isWhite();
    }
    return false;
}


King::King(bool white)
        : Piece{white} {
}

bool King::canMove(std::shared_ptr <Piece> const &sourcePiece, std::shared_ptr <Piece> const &killedPiece,
                   int const &sourceX, int const &sourceY,
                   int const &killedX, int const &killedY) const {

    if (isPotentialKillSameColor(sourcePiece, killedPiece))
        return false;

    int x = abs(sourceX - killedX);
    int y = abs(sourceY - killedY);
    if (x > 1)
        return false;

    if (y > 1)
        return false;

    return x + y <= 2;
}

PieceType King::getPieceType() const {
    return this->pieceType;
}

Queen::Queen(bool white)
        : Piece{white} {
}

bool Queen::canMove(std::shared_ptr <Piece> const &sourcePiece, std::shared_ptr <Piece> const &killedPiece,
                    int const &sourceX, int const &sourceY,
                    int const &killedX, int const &killedY) const {
    if (isPotentialKillSameColor(sourcePiece, killedPiece))
        return false;

    int x = abs(sourceX - killedX);
    int y = abs(sourceY - killedY);
    return (x == 0 || y == 0) || (x == y);
}

PieceType Queen::getPieceType() const {
    return this->pieceType;
}

Bishop::Bishop(bool white)
        : Piece{white} {
}

bool Bishop::canMove(std::shared_ptr <Piece> const &sourcePiece, std::shared_ptr <Piece> const &killedPiece,
                     int const &sourceX, int const &sourceY,
                     int const &killedX, int const &killedY) const {
    if (isPotentialKillSameColor(sourcePiece, killedPiece))
        return false;

    int x = abs(sourceX - killedX);
    int y = abs(sourceY - killedY);
    return x == y;
}

PieceType Bishop::getPieceType() const {
    return this->pieceType;
}

Knight::Knight(bool white)
        : Piece{white} {
}

bool Knight::canMove(std::shared_ptr <Piece> const &sourcePiece, std::shared_ptr <Piece> const &killedPiece,
                     int const &sourceX, int const &sourceY,
                     int const &killedX, int const &killedY) const {
    if (isPotentialKillSameColor(sourcePiece, killedPiece))
        return false;

    int x = abs(sourceX - killedX);
    int y = abs(sourceY - killedY);
    return (x == 1 && y == 2) || (x == 2 && y == 1);
}

PieceType Knight::getPieceType() const {
    return this->pieceType;
}

Rook::Rook(bool white)
        : Piece{white} {
}

bool Rook::canMove(std::shared_ptr <Piece> const &sourcePiece, std::shared_ptr <Piece> const &killedPiece,
                   int const &sourceX, int const &sourceY,
                   int const &killedX, int const &killedY) const {
    if (isPotentialKillSameColor(sourcePiece, killedPiece))
        return false;

    int x = abs(sourceX - killedX);
    int y = abs(sourceY - killedY);
    return x == 0 || y == 0;
}

PieceType Rook::getPieceType() const {
    return this->pieceType;
}

Pawn::Pawn(bool white)
        : Piece{white} {
}

bool Pawn::canMove(std::shared_ptr <Piece> const &sourcePiece, std::shared_ptr <Piece> const &killedPiece,
                   int const &sourceX, int const &sourceY,
                   int const &killedX, int const &killedY) const {
    if (isPotentialKillSameColor(sourcePiece, killedPiece))
        return false;

    int x{};
    int y{};

    if (sourcePiece->isWhite()) {
        x = killedX - sourceX;
        y = killedY - sourceY;
    } else {
        x = sourceX - killedX;
        y = sourceY - killedY;
    }
    if (((killedPiece == nullptr && x == 0) && // can move vertical without kill
         ((y == 1 || y == 2) && (this->isFirstMove() == true))) || // can move vertical 1 sq or 2 sq if first move
        (killedPiece != nullptr && abs(x) == 1 && y == 1)) // can move 1 sq diagonal if going for a kill
        return true;
    else
        return false;
}

PieceType Pawn::getPieceType() const {
    return this->pieceType;
}