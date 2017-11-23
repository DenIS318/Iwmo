#pragma once
#include <SFML/Network.hpp>
#include "Player.h"
//#include "Enemy.h"
#include <iostream>
#include <memory>
#include "Engine.h"

class Network
{
public:
	Network(sf::IpAddress& ip, Engine* engine,CSource* source,unsigned short port);
	void disconnect(Player* p);

	void send(Player* p);
	void sendPosition(Player* p);
	void receive(Player* p); //Add more later
	void sendMessage(Player* p, std::string& text);
	void sendMyName(Player* p);
	void getPlayerList(Player* p);
	void sendMaker(Player* p, bool maker);
	std::string getMessage() { return m_textMessage; }

private:
	vector<unique_ptr<kid>> playerKidlist;
	sf::TcpSocket connection;
	bool m_connected;
	Engine* m_engine;
	CSource* m_source;
	std::string m_textMessage;
	int packetCounter = 0;
	sf::Clock packetClock;
};