#ifndef MATCH_SCREEN_H
#define MATCH_SCREEN_H

#include "GameState.hpp"
#include "MatchMap.hpp"

#include <map>

class enum MatchState
{
    Pregame,
	WaitingForInput,
	WaitingForPackage
};

class MatchScreen : public GameState
{
public:
    MatchScreen(sf::RenderWindow *_window);
    ~MatchScreen();

    GameState update(sf::Time t0, std::vector<sf::Keyboard::Key> keyList) override;
    
private:
    sf::RenderWindow *window;
    MatchMap *map;
    MatchState currentState;
    MatchRole role;

    sf::TcpSocket *sock;

    std::map<sf::Keyboard::Key, Direction> kblayout;
};

#endif
