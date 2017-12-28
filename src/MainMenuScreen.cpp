#include "MainMenuScreen.hpp"

#include <iostream>

using namespace std;

MainMenuScreen::MainMenuScreen(sf::RenderWindow *_window)
{
    window = _window;
}

MainMenuScreen::~MainMenuScreen()
{
}

GameState MainMenuScreen::update(sf::Time t0, std::vector<sf::Event::KeyEvent> keyList)
{
    window->clear(sf::Color::Green);
    for (sf::Event::KeyEvent key : keyList)
    {
	if (key.code == sf::Keyboard::Num1)
	    return GameState::MatchCreator;
	else if (key.code == sf::Keyboard::Num2)
	    return GameState::MatchJoiner;
	else
	    cout << "Unhandled keyboard input for Main Menu" << endl;
    }
    
    return GameState::MainMenu;
}
