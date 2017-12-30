#include "sock.hpp"

#include <iostream>

using namespace std;

sf::Packet& operator <<(sf::Packet& packet, const PackageType& type)
{
    sf::Int8 i;
    switch (type)
    {
    case PackageType::Init:
	i = 1;
	break;

    case PackageType::CreateMatch:
	i = 2;
	break;

    case PackageType::JoinMatch:
	i = 3;
	break;

    case PackageType::GameStart:
	i = 4;
	break;

    default:
	cout << "Unknown PackageType in packet overload" << endl;
        i = -1;
    }
    packet << i;
    return packet;
}
sf::Packet& operator >>(sf::Packet& packet, PackageType& type)
{
    sf::Int8 i;
    packet >> i;

    switch (i)
    {
    case 1:
	type = PackageType::Init;
	break;

    case 2:
	type = PackageType::CreateMatch;
	break;

    case 3:
	type = PackageType::JoinMatch;
	break;

    case 4:
	type = PackageType::GameStart;
	break;

    case -1:
	cout << "Unknown PackageType in packet overload" << endl;
	break;

    default:
	cout << "Dunno what the fuck could posibly go so wrong" << endl;
    }
    
    return packet;
}

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

void sock_sendGameStart(sf::TcpSocket *sock1, sf::TcpSocket *sock2)
{
    sf::Packet packet;
    packet << PackageType::GameStart;
    sock1->send(packet);
    sock2->send(packet); //Can I reuse packet? Think so, seems to work
    cout << "Sent GameStart package" << endl;
}

void sock_receiveGameStart(sf::TcpSocket *sock)
{
    sf::Packet packet;
    sock->receive(packet);
    PackageType type;
    packet >> type;
    if (type == PackageType::GameStart)
	cout << "Received GameStart package" << endl;
    else
	cout << "Received something not GameStart package - probably fatal" << endl;
}
