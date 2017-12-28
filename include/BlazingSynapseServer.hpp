#ifndef BLAZING_SYNAPSE_SERVER_H
#define BLAZING_SYNAPSE_SERVER_H

#include "MatchMap.hpp"
#include "sock.hpp"

#include <thread>

enum class ServerState
{
    WaitingForCreation,
    WaitingForJoin,
    WaitingForPlayer1,
    WaitingForPlayer2
};

class BlazingSynapseServer
{
public:
    BlazingSynapseServer();
    ~BlazingSynapseServer();

    bool hasClosed();

private:
    void main_loop();
    std::thread *main_loop_thread;

    ServerState state;
    bool windowClosed;

    sf::TcpListener *listener;
    sf::TcpSocket *player1sock;
    sf::TcpSocket *player2sock;
    sf::RenderWindow *window;
    MatchMap *map;
};

#endif
