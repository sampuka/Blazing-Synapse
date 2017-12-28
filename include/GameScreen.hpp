#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState
{
    MainMenu,
    MatchCreator,
    MatchJoiner
};

class GameScreen
{
public:
    virtual ~GameScreen();
    
    virtual GameState update(sf::Time t0, std::vector<sf::Event::KeyEvent> keyList) = 0;

protected:
    sf::RenderWindow *window;
};

#endif
