#include "MapEvent.hpp"

#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

using namespace std;

MapEvent::MapEvent(EventType _type)
{
    type = _type;
}

MapEvent::~MapEvent()
{
}

/*
EventType MapEvent::getType()
{
    return type;
}

void MapEvent::setType(EventType _type)
{
    type = _type;
}
*/

sf::Packet& operator <<(sf::Packet& packet, const MapEvent& event)
{
    sf::Int8 i;
    switch(event.type)
    {
    case EventType::NoType:
	i = 1;
	break;
	
    case EventType::MoveSoldier:
        i = 2;
	break;

    case EventType::Action:
	i = 3;
	break;

    default:
	i = -1;
	cout << "Unhandled EventType in MapEvent packet overload" << endl;
    }
    return packet << i;
}
sf::Packet& operator >>(sf::Packet& packet, MapEvent& event)
{
    sf::Int8 i;
    packet >> i;
    switch(i)
    {
    case 1:
	event.type = EventType::NoType;
	break;
	
    case 2:
	event.type = EventType::MoveSoldier;
	break;

    case 3:
	event.type = EventType::Action;
	break;

    case -1:
	cout << "Unhandled EventType for MapEvent packet overload" << endl;
	break;

    default:
	cout << "Dunno how you fucked up this much tbh fam" << endl;
    }
    return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const vector<MapEvent>& eventList)
{
    sf::Int16 size = eventList.size();
    MapEvent event(EventType::NoType);

    packet << size;
    
    for (MapEvent event : eventList)
    {
	packet << event;
    }
    return packet;
}

sf::Packet& operator >>(sf::Packet& packet, vector<MapEvent>& eventList)
{
    sf::Int16 size;
    MapEvent event(EventType::NoType);
    packet >> size;

    while(size--)
    {
	packet >> event;
	eventList.push_back(event);
    }
    return packet;
}
