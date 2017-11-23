#include "Player.h"
Player::Player()
{

}
kid* Player::GetKid()
{
	return playerkid;
}
Player::Player(std::unique_ptr<sf::TcpSocket>* socket,kid* KID,Engine* engine,bool Maker, int id)
{
	m_engine = engine;
	m_id = id;
	m_socket = std::move(*socket);
	m_timeout = sf::seconds(0);
	playerkid = KID;
	maker = Maker;
}
/*Player::Player(kid* KID, Engine* engine, bool Maker, int id)
{
	m_engine = engine;
	m_name = "Noname";
	m_id = id;
	m_timeout = sf::seconds(0);
	playerkid = KID;
	maker = Maker;
}*/
bool Player::GetMaker()
{
	return maker;
}
void Player::SetMaker(bool b)
{
	maker = b;
}
void Player::SetSuperMaker(bool b)
{
	supermaker = b;
}
void Player::setName(const std::string name)
{
	m_name = name;
}

std::string Player::getName()
{
	return m_name;
}
void Player::setPrefix(string prefix)
{
	m_prefix = prefix;

}
string Player::getPrefix()
{
	return m_prefix;
}

int Player::getId()
{
	return m_id;
}
void Player::SetKid(kid* _kid)
{
	playerkid = _kid;
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