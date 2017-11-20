#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>
#include <string>
#include "kid.h"
class Player
{
public:
	Player(std::unique_ptr<sf::TcpSocket>* socket, int id);
	void setId(int id);
	void setName(const std::string name);
	std::string getName();

	int getId();

	sf::TcpSocket* getSocket();

	void setTimeout(sf::Time time);
	sf::Time getTimeout();


	void update(float deltaTime);
private:
	std::string m_name;
	int m_id;
	std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
	sf::Time m_timeout;
};