#ifndef BLAZING_SYNAPSE_CLIENT_H
#define BLAZING_SYNAPSE_CLIENT_H

#include "GameScreen.hpp"

#include <SFML/Graphics.hpp>
#include <Thread>

class BlazingSynapseClient
{
public:
    BlazingSynapseClient();
    ~BlazingSynapseClient();

    bool hasClosed();

private:
    std::Thread *main_loop_thread;
    std::vector<sf::Keyboard::Key> keyList;
    void main_loop();
    
    sf::RenderWindow *window;
    GameScreen *gameScreen;
    GameState gameState; 
    bool gameClosed;
};

#endif
