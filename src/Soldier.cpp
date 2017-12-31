#include "Soldier.hpp"

Soldier::Soldier(int _xpos, int _ypos, int _playerNumber)
{
    xpos = _xpos;
    ypos = _ypos;
    playerNumber = _playerNumber;
    alive = true;
    health = 100;
}

Soldier::~Soldier()
{
}

void Soldier::setPosition(int _xpos, int _ypos)
{
    xpos = _xpos;
    ypos = _ypos;
}

sf::Vector2i Soldier::getPosition()
{
    return sf::Vector2i(xpos, ypos);
}

void Soldier::setPlayerNumber(int _playerNumber)
{
    playerNumber = _playerNumber;
}

int Soldier::getPlayerNumber()
{
    return playerNumber;
}
