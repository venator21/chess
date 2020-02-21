#pragma once

class Player {
public:
	bool whiteSide;
	bool humanPlayer;

	bool isWhiteSide();
	bool isHumanPlayer();
};

class HumanPlayer : public Player {
	HumanPlayer(bool whiteSide);
};

class ComputerPlayer : public Player {
	ComputerPlayer(bool whiteSide);
};
