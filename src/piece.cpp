#include<iostream>
#include<string>
using namespace std;

class Piece {
private:
	bool killed = false;
	bool white = false;

public:
	void setWhite(bool white) {
		this->white = white;
	}
	void show() {
		cout << white << endl;
	}
};

class King: public Piece {
public:
	King(bool white) {
		this->setWhite(white);
	}
};

int main(){
	King k(false);
	k.show();

}
