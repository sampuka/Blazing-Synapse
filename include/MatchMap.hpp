#ifndef MATCH_MAP_H
#define MATCH_MAP_H

//#include "MapTile.hpp"

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

    //static void setupMap(std::string mapName, MatchMap *map);

    void drawMap(sf::RenderWindow *window);

    //void eventHandle(MapEvent *event);?
    
private:
    std::string mapName;
    unsigned int xsize;
    unsigned int ysize;
    //std::vector< std::vector<MapTile> > mapTiles;
};

#endif
