#include"Player.h"

Player::Player(bool whiteSide) : whiteSide(whiteSide) {}

bool Player::isWhiteSide() const {
    return this->whiteSide;
}

bool Player::isHumanPlayer() const {
    return this->humanPlayer;
}

HumanPlayer::HumanPlayer(bool whiteSide) : Player(whiteSide) {}

ComputerPlayer::ComputerPlayer(bool whiteSide) : Player(whiteSide) {}