#ifndef SOLDIER_H
#define SOLDIER_H

#include <SFML/System/Vector2.hpp>

class Soldier
{
public:
    Soldier(int _xpos, int _ypos);
    ~Soldier();

    void setPosition(int _xpos, int _ypos);
    sf::Vector2i getPosition();
    
private:
    int xpos;
    int ypos;
    int health;
    bool alive;
};

#endif
