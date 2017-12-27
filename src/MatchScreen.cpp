#include "MatchScreen.hpp"
#include "sock.hpp"

#include <iostream>

using namespace std;

MatchScreen::MatchScreen(sf::RenderWindow *_window, MatchRole _role)
{
    window = _window;
    currentState = MatchState::Pregame;
    role = _role;

    //Setup keyboard layout
    kblayout[sf::Keyboard::D] = Direction::E;
    kblayout[sf::Keyboard::A] = Direction::W;
    //kblayout[sf::Keyboard::] = Direction::;
    
    sock = sock_init();
    if (role == MatchRole::Creator)
	sock->createMap("Test map", &map);
    else if (role == MatchRole::Joiner)
	sock->joinMap(&map);
    else
	cout << "Unhandled MatchRole - Segfault inevitable probably" << endl;
}

MatchScreen::~MatchScreen()
{
    cout << "~MatchScreen()" << endl;
    delete map;
    //close socket?
    delete sock;
}

GameState MatchScreen::update(sf::Time t0, std::vector<sf::Keyboard::Key> keyList)
{
    for (sf::Keyboard::Key key : keyList)
    {
	switch (currentState)
	{
	case MatchState::Pregame
	    //No keyboard handling for pregame, waiting for package
	    break;

	case MatchState::WaitingForPackage:
	    //No keyboard handling when waiting for package
	    break;

	case MatchState::WaitingForInput:
	    cout << "Unhandled input" << endl;
	    break;

	default:
	    cout << "Unhandled state in keyboard handling" << endl;
	}
    }

    if (currentState == MatchState::WaitingForPackage)
	sock_recv();

    map->drawMap(window);
    
}
