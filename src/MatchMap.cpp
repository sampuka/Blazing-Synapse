#include "MatchMap.hpp"

#include <iostream>

using namespace std;

MatchMap::MatchMap(string _mapName)
{
    mapName = _mapName;

    //MatchMap::setupMap(mapName, this);
}

MatchMap::~MatchMap()
{
}

void MatchMap::drawMap(sf::RenderWindow *window)
{
    window->clear(sf::Color::Blue);
}
