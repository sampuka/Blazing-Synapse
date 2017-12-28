#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "GameScreen.hpp"

class MainMenuScreen : public GameScreen
{
public:
    MainMenuScreen(sf::RenderWindow *window);
    ~MainMenuScreen();

    GameState update(sf::Time t0, std::vector<sf::Event::KeyEvent> keyList);
};

#endif
