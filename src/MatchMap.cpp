#include "MatchMap.hpp"

#include <iostream>

using namespace std;

MatchMap::MatchMap(string _mapName)
{
    mapName = _mapName;

    setupMap(mapName);
}

MatchMap::~MatchMap()
{
}

void MatchMap::drawMap(sf::RenderWindow *window)
{
    window->clear(bgcolor);
    sf::RectangleShape shape(sf::Vector2f(10,10));

    for(unsigned int i = 0; i < xsize; i++)
    {
	for (unsigned int j = 0; j < ysize; j++)
	{
	    switch(mapTiles[i][j].getType())
	    {
	    case TileType::Wall:
		shape.setFillColor(sf::Color(50,50,50));
		shape.setPosition(i*10,j*10);
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
}

string MatchMap::getMapName()
{
    return mapName;
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
    }
}

		    
