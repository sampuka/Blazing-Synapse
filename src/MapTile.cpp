#include "MapTile.hpp"

MapTile::MapTile(TileType _tileType)
{
    tileType = _tileType;
}

MapTile::~MapTile()
{
}

TileType MapTile::getType()
{
    return tileType;
}
