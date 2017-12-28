#include "BlazingSynapseClient.hpp"

#include "MainMenuScreen.hpp"
#include "MatchScreen.hpp"

#include <iostream>

using namespace std;

BlazingSynapseClient::BlazingSynapseClient()
{
    gameClosed = false;
    gameState = GameState::MainMenu;
    window = new sf::RenderWindow(sf::VideoMode(600, 600), "Blazing Synapse Client");
    gameScreen = new MainMenuScreen(window); //Screen game opens on

    main_loop_thread = new thread(&BlazingSynapseClient::main_loop, this);
}

BlazingSynapseClient::~BlazingSynapseClient()
{
    //Close thread?
    delete window;
    delete gameScreen;
}

bool BlazingSynapseClient::hasClosed()
{
    return gameClosed;
}

void BlazingSynapseClient::main_loop()
{
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    GameState nextState = gameState;
    std::vector<sf::Event::KeyEvent> keyList;
    while (window->isOpen())
    {
	//Switch screens if needed
	if (nextState != gameState)
	{
	    cout << "Switching state" << endl;
	    switch (nextState)
	    {
	    case GameState::MainMenu:
		delete gameScreen;
		gameScreen = new MainMenuScreen(window);
		break;

	    case GameState::MatchCreator:
		delete gameScreen;
		gameScreen = new MatchScreen(window, MatchRole::Creator);
		break;

	    case GameState::MatchJoiner:
		delete gameScreen;
		gameScreen = new MatchScreen(window, MatchRole::Joiner);
		break;

	    default:
		cout << "Cannot switch to unhandled state" << endl;
	    }
	    gameState = nextState;
	}
	
	//Update keyList to be all new KeyPressed since last frame
	keyList.clear();
	while(window->pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window->close();
	    
	    if (event.type == sf::Event::KeyPressed)
		keyList.push_back(event.key);
	}
	
	time = clock.restart();
	//cout << "Time: " << time.asMilliseconds() << endl;
	nextState = gameScreen->update(time, keyList);

	cout << '.' << flush;
	sf::sleep(sf::milliseconds(200));
	window->display();
    }

    gameClosed = true;
}
