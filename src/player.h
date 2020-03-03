#pragma once

class Player {
protected:
	bool whiteSide;
	bool humanPlayer;
public:
	bool isWhiteSide();
	bool isHumanPlayer();
};

class HumanPlayer : public Player {
private:
	bool humanPlayer = true;
public:
	HumanPlayer(bool whiteSide);
};

class ComputerPlayer : public Player {
private:
	bool humanPlayer = false;
public:
	ComputerPlayer(bool whiteSide);
};
