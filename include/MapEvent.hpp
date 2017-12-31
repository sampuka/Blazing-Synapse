#ifndef MAP_EVENT_H
#define MAP_EVENT_H

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

enum class EventType
{
    NoType,
    MoveSoldier,
    Action
};

struct MoveSoldierEvent
{
    int activeSoldier;
    Direction dir;
};

union EventInfo
{
    MoveSoldierEvent MoveSoldier;
};

class MapEvent
{
public:
    MapEvent(EventType _type);
    ~MapEvent();

    EventType type;
    EventInfo info;
};

#endif
