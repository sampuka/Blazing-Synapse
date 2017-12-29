#include "sock.hpp"

#include <iostream>

using namespace std;

sf::TcpSocket* sock_client_init()
{
    cout << "Connecting to server... ";
    sf::TcpSocket *sock = new sf::TcpSocket;
    sf::Socket::Status status = sock->connect(sf::IpAddress::LocalHost, 12345);
    if (status != sf::Socket::Done)
    {
	cout << "Socket connect failed - Segfault inevitable probably" << endl;
    }
    else
	cout << "Connected!" << endl;

    return sock;
}

sf::TcpListener* sock_server_init()
{
    cout << "Beginning to listen... " << flush;
    sf::TcpListener *listener = new sf::TcpListener;
    sf::Socket::Status status = listener->listen(12345);
    if (status != sf::Socket::Done)
    {
	cout << "Failed :( - Segfault inevitable probably" << endl;
    }
    else
	cout << "Succes" << endl;
    
    return listener;
}

sf::TcpSocket* sock_listen(sf::TcpListener *listener)
{
    cout << "Waiting for connection... " << flush;
    sf::TcpSocket *client = new sf::TcpSocket;
    if (listener->accept(*client) != sf::Socket::Done)
    {
	cout << "failed :(" << endl;
    }
    else
	cout << "Succes" << endl;

    return client;
}

void sock_createMatch(sf::TcpSocket *sock, string mapName, MatchMap **map)
{
    cout << "Creating Match" << endl;
    (*map) = new MatchMap(mapName);
    sf::Packet packet;
    packet << mapName;
    sock->send(packet);
}

MatchMap* sock_letCreateMatch(sf::TcpSocket *sock)
{
    cout << "Waiting for map creation... " << flush;
    sf::Packet packet;
    sock->receive(packet);
    cout << "Recieved!" << endl;
    string mapName;
    packet >> mapName;
    return new MatchMap(mapName);
}

void sock_joinMatch(sf::TcpSocket *sock, MatchMap **map)
{
    cout << "Joining Match" << endl;
    sf::Packet packet;
    sock->receive(packet);
    string mapName;
    packet >> mapName;
    (*map) = new MatchMap(mapName);
}

void sock_letJoinMatch(sf::TcpSocket *sock, string mapName)
{
    cout << "Waiting for join... " << flush;
    sf::Packet packet;
    packet << mapName;
    sock->send(packet);
    cout << "Sent!" << endl;
}
