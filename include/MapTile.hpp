#ifndef MAP_TILE_H
#define MAP_TILE_H

enum class TileType
{
    Empty,
    Wall
};

class MapTile
{
public:
    MapTile(TileType _tileType);
    ~MapTile();

    TileType getType();

private:
    TileType tileType;
};

#endif
