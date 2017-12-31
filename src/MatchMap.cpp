#include "MatchMap.hpp"

#include <iostream>

using namespace std;

MatchMap::MatchMap(string _mapName)
{
    mapName = _mapName;

    setupMap(mapName);
}

MatchMap::MatchMap(sf::Color _bgcolor, std::string _mapName, unsigned int _xsize, unsigned int _ysize, std::vector< std::vector<MapTile> > _mapTiles, std::vector<Soldier> _soldiers)
{
    bgcolor = _bgcolor;
    mapName = _mapName;
    xsize = _xsize;
    ysize = _ysize;
    mapTiles = _mapTiles;
    soldiers = _soldiers;
    //player1soldiers = _player1soldiers;
    //player2soldiers = _player2soldiers;
}

MatchMap::~MatchMap()
{
}

void MatchMap::drawMap(sf::RenderWindow *window)
{
    window->clear(bgcolor);
    sf::RectangleShape shape(sf::Vector2f(10,10));
    sf::CircleShape circ(10);

    for(unsigned int i = 0; i < xsize; i++)
    {
	for (unsigned int j = 0; j < ysize; j++)
	{
	    switch(mapTiles[i][j].getType())
	    {
	    case TileType::Wall:
		shape.setFillColor(sf::Color(50,50,50));
		shape.setPosition(i*10, j*10);
		window->draw(shape);
		break;
		
	    case TileType::Empty:
		//Don't draw empty tiles
		break;
		
	    default:
		break;
	    }		
	}
    }

    for (Soldier sol : soldiers)
    {
	if (sol.getPlayerNumber() == 1)
	    circ.setFillColor(sf::Color::Blue);
	else
	    circ.setFillColor(sf::Color::Red);

        circ.setPosition(sol.getPosition().x *10, sol.getPosition().y *10);
	window->draw(circ);
    }
    
    /*
    circ.setFillColor(sf::Color::Blue);
    for (Soldier sol : player1soldiers)
    {
	circ.setPosition(sol.getPosition().x *10, sol.getPosition().y* 10);
	window->draw(circ);
    }

    circ.setFillColor(sf::Color::Red);
    for (Soldier sol : player2soldiers)
    {
	circ.setPosition(sol.getPosition().x *10, sol.getPosition().y *10);
	window->draw(circ);
    }
    */
}

bool MatchMap::possibleEvents(vector<MapEvent> eventList)
{
    bool possible = true;
    MatchMap testmap(bgcolor, mapName, xsize, ysize, mapTiles, soldiers);
    for (MapEvent event : eventList)
    {
	if (!executeEvent(&testmap, event))
	    possible = false;
    }

    return possible;
}

bool MatchMap::executeEvent(MatchMap *map, MapEvent event)
{
    bool succes = true;
    
    switch (event.type)
    {
    case EventType::MoveSoldier:
    {
	//cout << "event.info.MoveSoldier-activeSoldier: " << event.info.MoveSoldier.activeSoldier << endl;
	int xpos = map->getSoldier(event.info.MoveSoldier.activeSoldier).getPosition().x;
	int ypos = map->getSoldier(event.info.MoveSoldier.activeSoldier).getPosition().y;

	cout << "Moving soldier at (" << xpos << "," << ypos << ")" << endl;
	
	switch(event.info.MoveSoldier.dir)
	{
	case Direction::E:
	    if (
		isClear(xpos+2, ypos) &&
		isClear(xpos+2, ypos+1)
		)
	    {
		map->moveSoldier(event.info.MoveSoldier.activeSoldier, xpos+1, ypos);
		succes = true;
	    }
	    else
		succes = false;
	    break;
	    
	case Direction::W:
	    if (
		isClear(xpos-1, ypos) &&
		isClear(xpos-1, ypos+1)
		)
	    {
		map->moveSoldier(event.info.MoveSoldier.activeSoldier, xpos-1, ypos);
		succes = true;
	    }
	    else
		succes = false;
	    break;

	default:
	    cout << "Unhandled direction for moving soldier in executeEvent()" << endl;
	}
    }
	break;

    case EventType::Action:
	break;

    default:
	cout << "Unhandled EventType in executeEvent()" << endl;
    }

    return succes;
}

void MatchMap::executeEvents(vector<MapEvent> eventList)
{
    for (MapEvent event : eventList)
    {
	executeEvent(this, event);
    }
}

string MatchMap::getMapName()
{
    return mapName;
}

Soldier MatchMap::getSoldier(int soldierNumber)
{
    return soldiers[soldierNumber];
}

int MatchMap::getSoldierCount()
{
    return soldiers.size();
}

void MatchMap::setupMap(string mapName)
{
    if (mapName == "Test map")
    {
	cout << "Creating \"" << mapName << "\"" << endl;
	bgcolor = sf::Color(200,200,200);
	xsize = 30;
	ysize = 30;
	
	for (unsigned int i = 0; i < xsize; i++)
	{
	    mapTiles.push_back({});
	    for (unsigned int j = 0; j < ysize; j++)
	    {
		if (i == 0 || i == xsize-1 || j == 0 || j == ysize-1)
		    mapTiles[i].push_back(MapTile(TileType::Wall));
		else
		    mapTiles[i].push_back(MapTile(TileType::Empty));
	    }
	}
	mapTiles[14][15] = MapTile(TileType::Wall);
	mapTiles[15][15] = MapTile(TileType::Wall);
	mapTiles[15][14] = MapTile(TileType::Wall);
	mapTiles[16][15] = MapTile(TileType::Wall);
	mapTiles[15][16] = MapTile(TileType::Wall);

	soldiers.push_back(Soldier(2, 2, 1));
	soldiers.push_back(Soldier(4, 4, 1));
	soldiers.push_back(Soldier(2, 26, 2));
	soldiers.push_back(Soldier(4, 24, 2));
    }
}

bool MatchMap::isClear(int xpos, int ypos)
{
    if (xpos < 0 || xpos > static_cast<int>(xsize -1) || ypos < 0 || ypos > static_cast<int>(ysize-1))
	return false;
    TileType type = mapTiles[xpos][ypos].getType();

    if (type == TileType::Empty)
	return true;
    else
	return false;
}

void MatchMap::moveSoldier(int soldierNumber, int xpos, int ypos)
{
    soldiers[soldierNumber].setPosition(xpos, ypos);
}
