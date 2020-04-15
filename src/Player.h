#pragma once

class Player {
public:
    Player()=default;
    Player(bool whiteSide);
    bool isWhiteSide() const;
    bool isHumanPlayer() const;
private:
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
 public:
  ComputerPlayer(bool whiteSide);
private:
  bool humanPlayer = false;
};