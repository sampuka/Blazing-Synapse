#ifndef MATCH_MAP_H
#define MATCH_MAP_H

#include "MapTile.hpp"
#include "Soldier.hpp"
#include "MapEvent.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MatchMap
{
public:
    MatchMap(std::string _mapName);
    MatchMap(sf::Color _bgcolor, std::string _mapName, unsigned int _xsize, unsigned int _ysize, std::vector< std::vector<MapTile> > _mapTiles, std::vector<Soldier> soldiers);
    ~MatchMap();

    void drawMap(sf::RenderWindow *window);
    
    bool possibleEvents(std::vector<MapEvent> eventList);
    bool executeEvent(MatchMap *map, MapEvent event);
    void executeEvents(std::vector<MapEvent> eventList);

    std::string getMapName();
    Soldier getSoldier(int soldierNumber);
    int getSoldierCount();
    
private:
    void setupMap(std::string mapName);
    bool isClear(int xpos, int ypos);
    void moveSoldier(int soldierNumber, int xpos, int ypos);
    
    sf::Color bgcolor;
    std::string mapName;
    unsigned int xsize;
    unsigned int ysize;
    std::vector< std::vector<MapTile> > mapTiles;
    std::vector<Soldier> soldiers;
    //std::vector<Soldier> player1soldiers;
    //std::vector<Soldier> player2soldiers;
};

#endif
