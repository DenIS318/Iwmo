#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>
#include <string>
#include "kid.h"
#include "Engine.h"
using namespace std;
class Player
{
public:
	Player(std::unique_ptr<sf::TcpSocket>* socket, kid* KID,Engine* engine,bool maker,int id);
	void setId(int id);
	void setPrefix(string prefix);
	std::string getPrefix();
	void setName(const std::string name);
	std::string getName();

	int getId();

	sf::TcpSocket* getSocket();

	void setTimeout(sf::Time time);
	sf::Time getTimeout();

	void SetMaker(bool b);
	void SetSuperMaker(bool b);
	void update(float deltaTime);
private:
	kid* playerkid;
	Engine* m_engine;
	std::string m_name;
	bool maker;
	bool supermaker;
	string m_prefix;
	int m_id;
	std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
	sf::Time m_timeout;
};