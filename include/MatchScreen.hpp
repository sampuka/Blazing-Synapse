#ifndef MATCH_SCREEN_H
#define MATCH_SCREEN_H

#include "GameScreen.hpp"
#include "MatchMap.hpp"
#include "sock.hpp"

#include <thread>
#include <map>

enum class MatchState
{
    Pregame,
	WaitingForInput,
	WaitingForPackage
};

class MatchScreen : public GameScreen
{
public:
    MatchScreen(sf::RenderWindow *_window, MatchRole _role);
    ~MatchScreen();

    GameState update(sf::Time t0, std::vector<sf::Event::KeyEvent> keyList) override;
    
private:
    void connection_handle_loop();
    std::thread *connection_handle_loop_thread;
    
    MatchMap *map;
    bool isMapCreated;
    MatchState currentState;
    MatchRole role;

    sf::TcpSocket *sock;

    std::map<sf::Keyboard::Key, Direction> kblayout;
};

#endif
