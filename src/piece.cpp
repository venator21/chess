#include<iostream>
#include<string>
using namespace std;

class Piece {
private:
	bool killed = false;
	bool white = false;

public:
	Piece(bool white) {
		this->setWhite(white);
	}
	void setWhite(bool white) {
		this->white = white;
	}
	bool isWhite() {
		return this->white;
	}
	void setKilled(bool killed) {
		this->killed = killed;
	}
	bool isKilled() {
		return this->killed;
	}
	virtual bool canMove() = 0; //TODO add arguments
};

class King: public Piece {
private:
	bool castlingDone = false;

	bool isValidCastling(){  //TODO add arguments

		if (this->isCastlingDone()) {
			return false;
		}
		//TODO Logic for returning true or false 
	}
public:
	King(bool white)
		: Piece{ white }{
	}
	bool isCastlingDone() {
		return this->castlingDone == true;
	}
	void setCastlingDone(bool castlingDone) {
		this->castlingDone = castlingDone;
	}
	virtual bool canMove() { //TODO add args and logic for returning true or false
		return 0;
	}
};


class Queen : public Piece {
public:
	Queen(bool white)
		: Piece{ white } {
	}
	virtual bool canMove() { //TODO add args and logic for returning true or false
		return 0;
	}
};

class Bishop : public Piece {
public:
	Bishop(bool white)
		: Piece{ white } {
	}
	virtual bool canMove() { //TODO add args and logic for returning true or false
		return 0;
	}
};

class Knight : public Piece {
public:
	Knight(bool white)
		: Piece{ white } {
	}
	virtual bool canMove() { //TODO add args and logic for returning true or false
		return 0;
	}
};

class Rook: public Piece {
public:
	Rook(bool white)
		: Piece{ white } {
	}
	virtual bool canMove() { //TODO add args and logic for returning true or false
		return 0;
	}
};

class Pawn : public Piece {
private:
	bool isValidEnPassant() {  //TODO add arguments
		//TODO Logic for returning true or false 
	}
	bool isValidPromotion() {  //TODO add arguments
	//TODO Logic for returning true or false 
	}

public:
	Pawn(bool white)
		: Piece{ white } {
	}
	void getPromoted() { //TODO implementation of promotion
	}
	virtual bool canMove() { //TODO add args and logic for returning true or false
		return 0;
	}
};




int main(){
	Queen q(true);
	cout << q.isWhite() << endl;
	cout << q.isKilled() << endl;
}
