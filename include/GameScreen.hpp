#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

enum class GameState
{
    MainMenu,
    Match
};

class GameScreen
{
public:
    virtual ~GameScreen();
    
    virtual GameState update(sf::Time t0, std::vector<sf::Keyboard::Key> keyList) = 0;
};

#endif
