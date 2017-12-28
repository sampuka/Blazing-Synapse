#include "BlazingSynapseServer.hpp"

#include <iostream>
#include <string>

using namespace std;

BlazingSynapseServer::BlazingSynapseServer()
{
    windowClosed = false;
    window = new sf::RenderWindow(sf::VideoMode(600,600), "Blazing Synapse Server");
    state = ServerState::WaitingForCreation;
    main_loop_thread = new thread(&BlazingSynapseServer::main_loop, this);
    listener = sock_server_init();
    player1sock = sock_listen(listener);
    //   string mapName;
    //map = new MatchMap();
    state = ServerState::WaitingForJoin;
    player2sock = sock_listen(listener);
}

BlazingSynapseServer::~BlazingSynapseServer()
{
    delete window;
    delete map;
    //close sock?
    delete listener;
    delete player1sock;
    delete player2sock;
    //Stop thread?
}

void BlazingSynapseServer::main_loop()
{
    sf::Event event;
    while (window->isOpen())
    {
	while(window->pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window->close();

	    if (event.type == sf::Event::KeyPressed)
	    {
		if (event.key.code == sf::Keyboard::Escape)
		    window->close();
	    }
	}
	
	if (state != ServerState::WaitingForCreation)
	{
	    window->clear(sf::Color::Black);
	    map->drawMap(window);
	}
	else
	    window->clear(sf::Color::Yellow);
	
	cout << '.' << flush;
	sf::sleep(sf::milliseconds(200));
	window->display();
    }

    windowClosed = true;
}

bool BlazingSynapseServer::hasClosed()
{
    return windowClosed;
}