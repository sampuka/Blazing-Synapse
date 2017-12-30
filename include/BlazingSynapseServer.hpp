#ifndef BLAZING_SYNAPSE_SERVER_H
#define BLAZING_SYNAPSE_SERVER_H

#include "MatchMap.hpp"
#include "sock.hpp"

#include <thread>

enum class ServerState
{
    WaitingForCreation,
    WaitingForJoin,
    WaitingForPlayerInput
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

    void connection_handle_loop();
    std::thread *connection_handle_loop_thread;

    ServerState state;
    bool windowClosed;
    MatchMap *map;

    sf::TcpListener *listener;
    sf::TcpSocket *player1sock;
    sf::TcpSocket *player2sock;
    sf::RenderWindow *window;
};

#endif
