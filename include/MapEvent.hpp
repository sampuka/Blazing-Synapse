#ifndef MAP_EVENT_H
#define MAP_EVENT_H

enum class EventType
{
    NoType,
    MoveSoldier,
    Action
};

class MapEvent
{
public:
    MapEvent(EventType _type);
    ~MapEvent();

    EventType type;
    
    /*
    EventType getType();
    void setType(EventType);
    
private:
    EventType type;
    */
};

#endif
