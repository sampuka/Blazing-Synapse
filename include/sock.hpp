#ifndef SOCK_H_SAFE //Added "_SAFE" because I felt like "SOCK_H" wasn't very unique
#define SOCK_H_SAFE

#include "MatchMap.hpp"

#include <SFML/Network.hpp>
#include <string>

enum class MatchRole
{
    Creator,
    Joiner
};

enum class PackageType
{
    Init,
    CreateMatch,
    JoinMatch,
    GameStart
};

sf::TcpSocket* sock_client_init();
sf::TcpListener* sock_server_init();

sf::TcpSocket* sock_listen(sf::TcpListener *listener);

void sock_createMatch(sf::TcpSocket *sock, std::string mapName, MatchMap **map);
MatchMap* sock_letCreateMatch(sf::TcpSocket *sock);

void sock_joinMatch(sf::TcpSocket *sock, MatchMap **map);
void sock_letJoinMatch(sf::TcpSocket *sock, std::string mapName);

void sock_sendGameStart(sf::TcpSocket *sock1, sf::TcpSocket *sock2);
void sock_receiveGameStart(sf::TcpSocket *sock);


#endif
