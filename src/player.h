#pragma once

class Player {
 public:
	bool isWhiteSide();
	bool isHumanPlayer();
 protected:
  bool whiteSide;
  bool humanPlayer;
};

class HumanPlayer : public Player {
 public:
	HumanPlayer(bool whiteSide);
 private:
  bool humanPlayer = true;
};

class ComputerPlayer : public Player {
 private:
  bool humanPlayer = false;
 public:
  ComputerPlayer(bool whiteSide);
};