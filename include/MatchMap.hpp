#ifndef MATCH_MAP_H
#define MATCH_MAP_H

#include "MapTile.hpp"
#include "Soldier.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class Direction
{
    N,
    E,
    S,
    W,
    NE,
    SE,
    SW,
    NW
};

class MatchMap
{
public:
    MatchMap(std::string _mapName);
    ~MatchMap();

    void drawMap(sf::RenderWindow *window);

    //void eventHandle(MapEvent *event);?

    std::string getMapName();
    
private:
    void setupMap(std::string mapName);
    
    sf::Color bgcolor;
    std::string mapName;
    unsigned int xsize;
    unsigned int ysize;
    std::vector< std::vector<MapTile> > mapTiles;
    std::vector<Soldier> player1soldiers;
    std::vector<Soldier> player2soldiers;
};

#endif
