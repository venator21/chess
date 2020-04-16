#pragma once

class Player {
public:
    Player() = default;

    explicit Player(bool whiteSide);

    bool isWhiteSide() const;

    bool isHumanPlayer() const;

private:
    bool whiteSide{};
    bool humanPlayer{};
};

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(bool whiteSide);

private:
    bool humanPlayer = true;
};

class ComputerPlayer : public Player {
public:
    explicit ComputerPlayer(bool whiteSide);

private:
    bool humanPlayer = false;
};