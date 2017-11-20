#include "Player.h"

Player::Player(std::unique_ptr<sf::TcpSocket>* socket, int id)
{
	m_name = "Noname";
	m_id = id;
	m_socket = std::move(*socket);
	m_timeout = sf::seconds(0);
}

void Player::setName(const std::string name)
{
	m_name = name;
}

std::string Player::getName()
{
	return m_name;
}

int Player::getId()
{
	return m_id;
}
void Player::setId(int id)
{
	m_id = id;
}

sf::TcpSocket* Player::getSocket()
{
	return m_socket.get();
}

void Player::setTimeout(sf::Time time)
{
	m_timeout = time;
}

sf::Time Player::getTimeout()
{
	return m_timeout;
}

void Player::update(float deltaTime)
{

}