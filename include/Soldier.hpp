#ifndef SOLDIER_H
#define SOLDIER_H

#include <SFML/System/Vector2.hpp>

class Soldier
{
public:
    Soldier(int _xpos, int _ypos, int _playerNumber);
    ~Soldier();

    void setPosition(int _xpos, int _ypos);
    sf::Vector2i getPosition();

    void setPlayerNumber(int _playerNumber);
    int getPlayerNumber();
    
private:
    int xpos;
    int ypos;
    int playerNumber;
    int health;
    bool alive;
};

#endif
