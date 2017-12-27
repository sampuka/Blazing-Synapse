#include "BlazingSynapseClient.hpp"

#include "MainMenuScreen.hpp"
#include "MatchScreen.hpp"

#include <iostream>

using namespace std;

BlazingSynapseClient::BlazingSynapseClient()
{
    gameClosed = false;
    gameState = GameState::Match;
    window = new sf::RenderWindow(sf::VideoMode(600, 600), "Blazing Synapse Client");
    gameScreen = new MainMenuScreen; //Screen game opens on

    main_loop_thread = new Thread(&main_loop, this);
}

BlazingSynapseClient::~BlazingSynapseClient()
{
}

void BlazingSynapseClient::main_loop()
{
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    GameState nextState = currentState;
    while (window->isOpen())
    {
	//Switch screens if needed
	if (nextState != currentState)
	{
	    cout << "Switching state" << endl;
	    switch (nextState)
	    {
	    case GameState::MainMenu:
		delete gameScreen;
		gameScreen = new MainMenuScreen;
		break;

	    case GameState::Match:
		delete gameScreen;
		gameScreen = new Match;
		break;

	    default:
		cout << "Cannot switch to unhandled state" << endl;
	    }
	}
	//Update keyList to be all new KeyPressed since last frame
	keyList.clear();
	while(window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window->close();
	    
	    if (event.type == sf::Event::KeyPressed)
		keyList.push_back(event.type);
	}
	time = clock.restart();
	cout << "Time: " << time.asMilliseconds() << endl;
	nextState = gameScreen->update(time, keyList);

	sf::sleep(sf::milliseconds(200));
	window->display();
    }

    gameClosed = true;
}
