#include "MatchScreen.hpp"
#include "sock.hpp"

#include <iostream>

using namespace std;

MatchScreen::MatchScreen(sf::RenderWindow *_window, MatchRole _role)
{
    window = _window;
    role = _role;

    if (role == MatchRole::Creator)
	playerNumber = 1;
    else
	playerNumber = 2;

    isMapCreated = false;
    activeSoldier = 0;
    
    //Setup keyboard layout
    kblayout[sf::Keyboard::D] = Direction::E;
    kblayout[sf::Keyboard::A] = Direction::W;
    //kblayout[sf::Keyboard::] = Direction::;

    connection_handle_loop_thread = new thread(&MatchScreen::connection_handle_loop, this);
}

MatchScreen::~MatchScreen()
{
    cout << "~MatchScreen()" << endl;
    delete map;
    sock->disconnect();
    delete sock;
}

GameState MatchScreen::update(sf::Time t0, std::vector<sf::Event::KeyEvent> keyList)
{
    MapEvent event(EventType::NoType);
    
    for (sf::Event::KeyEvent key : keyList)
    {
	switch (currentState)
	{
	case MatchState::Pregame:
	    //No keyboard handling for pregame, waiting for GameStart package
	    break;

	case MatchState::WaitingForPackage:
	    //No keyboard handling when waiting for package
	    break;

	case MatchState::WaitingForInput:
	    if (key.code == sf::Keyboard::Return)
	    {
		nextSoldier();
	    }
	    else if (kblayout.count(key.code))
	    {
		cout << "Creating MoveSoldier event" << endl;
		event.type = EventType::MoveSoldier;
		event.info.MoveSoldier.activeSoldier = activeSoldier;
		event.info.MoveSoldier.dir = kblayout[key.code];
		eventList.push_back(event);

		if(!map->possibleEvents(eventList))
		{
		    cout << "Impossible event" << endl;
		    eventList.pop_back();
		}
	    }
	    else
		cout << "Unhandled keyboard input" << endl;
	    break;

	default:
	    cout << "Unhandled state in keyboard handling" << endl;
	}
    }

    //Display switch
    window->clear();
    switch (currentState)
    {
    case MatchState::Pregame:
	if (isMapCreated)
	    map->drawMap(window);
	else
	    window->clear(sf::Color::Blue);
	break;

    case MatchState::WaitingForInput:
	map->drawMap(window);
	break;

    case MatchState::WaitingForPackage:
	map->drawMap(window);
	break;

    default:
	cout << "Unhandled MatchState for display switch" << endl;
	break;
    }

    switch (role)
    {
    case MatchRole::Creator:
	return GameState::MatchCreator;
	break;
	
    case MatchRole::Joiner:
	return GameState::MatchJoiner;
	break;
    }
    cout << "Unhandled MatchRole - probably fatal, going to main menu screen" << endl;
    return GameState::MainMenu;
}

void MatchScreen::connection_handle_loop()
{
    sock = sock_client_init();
    if (role == MatchRole::Creator)
    {
	sock_createMatch(sock, "Test map", &map);
    }
    else if (role == MatchRole::Joiner)
    {
	sock_joinMatch(sock, &map);
    }
    else
	cout << "Unhandled MatchRole - Segfault inevitable probably" << endl;
    isMapCreated = true;
    currentState = MatchState::Pregame;

    sock_receiveGameStart(sock);
    currentState = MatchState::WaitingForInput;
}

void MatchScreen::updateActiveSoldier()
{
    activeSoldier = 0;
}

void MatchScreen::nextSoldier()
{
    int currentSoldier = activeSoldier;
    if (currentSoldier == map->getSoldierCount()-1)
	currentSoldier = 0;
    else
	currentSoldier++;
    for (int i = currentSoldier; i < map->getSoldierCount(); i++)
    {
	if (map->getSoldier(i).getPlayerNumber() == playerNumber)
	{
	    activeSoldier = i;
	    return;
	}
    }

    currentState = MatchState::WaitingForPackage;
    //sock_sendEvents(eventList);
    map->executeEvents(eventList);
}
