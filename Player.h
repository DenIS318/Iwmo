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
	//Player(kid* KID, Engine* engine, bool Maker, int id);
	Player(std::unique_ptr<sf::TcpSocket>* socket, kid* KID,Engine* engine,bool maker,int id);
	void setId(int id);
	void setPrefix(string prefix);
	std::string getPrefix();
	void setName(const std::string name);
	std::string getName();
	//empty player
	Player();
	int getId();

	sf::TcpSocket* getSocket();

	void setTimeout(sf::Time time);
	sf::Time getTimeout();

	void SetMaker(bool b);
	void SetSuperMaker(bool b);
	void update(float deltaTime);
	bool GetMaker();
	void SetKid(kid* _kid);
	kid* GetKid();
private:
	kid* playerkid;
	Engine* m_engine;
	std::string m_name = "Noname";
	bool maker;
	bool supermaker;
	string m_prefix;
	int m_id;
	std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
	sf::Time m_timeout;
};