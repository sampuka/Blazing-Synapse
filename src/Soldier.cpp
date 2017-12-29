#include "Soldier.hpp"

Soldier::Soldier(int _xpos, int _ypos)
{
    xpos = _xpos;
    ypos = _ypos;
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
