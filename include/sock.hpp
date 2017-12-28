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

sf::TcpSocket* sock_client_init();
sf::TcpListener* sock_server_init();

sf::TcpSocket* sock_listen(sf::TcpListener *listener);

void sock_createMatch(sf::TcpSocket *sock, std::string mapName, MatchMap **map);
void sock_joinMatch(sf::TcpSocket *sock, MatchMap **map);

#endif
