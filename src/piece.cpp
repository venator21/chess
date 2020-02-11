#include<iostream>

using namespace std;

class Piece {

public:
	virtual void show() = 0;

};

public Derived: public Piece{
	void show() { cout << "derived func called" << endl; }
};

int main(){
}
