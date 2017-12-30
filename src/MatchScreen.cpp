#include "MatchScreen.hpp"
#include "sock.hpp"

#include <iostream>

using namespace std;

MatchScreen::MatchScreen(sf::RenderWindow *_window, MatchRole _role)
{
    window = _window;
    role = _role;

    isMapCreated = false;
    
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
    for (sf::Event::KeyEvent key : keyList)
    {
	switch (currentState)
	{
	case MatchState::Pregame:
	    //No keyboard handling for pregame, waiting for package
	    break;

	case MatchState::WaitingForPackage:
	    //No keyboard handling when waiting for package
	    break;

	case MatchState::WaitingForInput:
	    cout << "Unhandled keyboard input" << endl;
	    break;

	default:
	    cout << "Unhandled state in keyboard handling" << endl;
	}
    }

    //if (currentState == MatchState::WaitingForPackage)
	//sock_recv();

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
    cout << "Unhandled MatchRole - Segfault inevitable probably" << endl;
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
