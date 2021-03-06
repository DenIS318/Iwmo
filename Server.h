#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Player.h"
#include "Engine.h"
using namespace Iwmo;
class Server
{
public:
	Server(Engine* engine, CSource* source);
	void run();
	void close();
private:
	void Server::SetSuperMaker(bool b, int id);
	void sendPacket(sf::Packet& packet, unsigned int skip = -1);
	bool m_isRunning;
	sf::IpAddress m_ipAdress;
	unsigned short m_port;

	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;

	int m_maxPlayerNumber;
	int m_currentID;
	int m_playerNumber;

	std::vector<Player> m_playerList;
	char m_tmp[1400];

	sf::Clock m_clock;
	Engine* m_engine;
	CSource* m_ls;

};