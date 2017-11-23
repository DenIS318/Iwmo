#include "Network.h"
#define getID getId
#define getDirection getPosition
Network::Network(sf::IpAddress& ip,Engine* eng,CSource* source, unsigned short port) : m_connected(false)
{
	m_engine = eng;
	m_source = source;
	if (connection.connect(ip, port, sf::seconds(5)) != sf::Socket::Done)
	{
		std::cout << "Error connecting to server" << std::endl;
	}
	else
	{
		connection.setBlocking(false);
		std::cout << "Connected" << std::endl;
	}
}


void Network::disconnect(Player* p) //Disconnect the player from the server
{
	sf::Packet temp;
	temp << 1;
	temp << p->getID();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending disconnect command to server" << std::endl;
	}
	else
	{
		std::cout << "Disconnected" << std::endl;
	}
}

void Network::send(Player* p)
{
	sf::Packet temp;
	temp << 3;
	temp << p->getID();
	//temp << p->getDirection().x;
	//temp << p->getDirection().y;

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending data to server" << std::endl;
	}


}

void Network::sendPosition(Player* p)
{
	if (m_connected)
	{
		sf::Packet temp;
		temp << 4;
		temp << p->getID();
		//temp << p->getPosition().x;
		//temp << p->getPosition().y;

		if (connection.send(temp) != sf::Socket::Done)
		{
			std::cout << "Error sending data to server" << std::endl;
		}
	}

}


void Network::sendMessage(Player* p, std::string& text)
{
	sf::Packet temp;
	temp << 5;
	temp << p->getID();
	temp << text;

	if (text.length() > 2)
		if (connection.send(temp) != sf::Socket::Done)
		{
			std::cout << "Error sending text message to server" << std::endl;
		}
}


void Network::sendMyName(Player* p)
{
	sf::Packet temp;
	temp << 6;
	temp << p->getID();
	temp << p->getName();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending my name" << std::endl;
	}

}

void Network::getPlayerList(Player* p)
{
	sf::Packet temp;
	temp << 7;
	temp << p->getID();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending getPlayerList to server" << std::endl;
	}
}
void Network::sendMaker(Player* p,bool maker)
{
	sf::Packet temp;
	temp << 12;
	temp << p->getID();
	temp << maker;

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending maker to server" << std::endl;
	}
}


void Network::receive( Player* p)
{

	sf::Packet receivePacket;
	int type, id;
	if (connection.receive(receivePacket) == sf::Socket::Done)
	{
		receivePacket >> type;
		receivePacket >> id;

		if (type == 0) // you connected to server, get your ID
		{
			p->setId(id);
			std::cout << "I connected to server, my ID: " << p->getID() << std::endl;
			this->sendMyName(p);
			sendMaker(p, m_engine->ClientIsMaker);
			//sf::sleep(sf::milliseconds(50));
			this->getPlayerList(p);
			m_connected = true;
		}
		else if (type == 1) // disconnected
		{
			m_textMessage = "Player " + p->getName() + " disconnected.";
			/*for (unsigned int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i]->getID() == id)
				{
					m_textMessage = "Player " + enemies[i]->getName() + " disconnected.";
					std::cout << "Enemy: " << enemies[i]->getID() << " deleted " << std::endl;
					enemies.erase(enemies.begin() + i);
				}
			}*/
		}
		else if (type == 2)
		{
			std::cout << "Server is full" << std::endl;
		}

		else if (type == 3) // get move direction of enemys
		{
			/*for (unsigned int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i]->getID() == id)
				{
					sf::Vector2f dir;
					receivePacket >> dir.x;
					receivePacket >> dir.y;

					enemies[i]->setDirection(dir);
					break;
				}

			}*/
		}
		else if (type == 4) //Set player position to the recived position
		{

			/*for (unsigned int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i]->getID() == id)
				{
					sf::Vector2f pos;
					receivePacket >> pos.x;
					receivePacket >> pos.y;

					enemies[i]->setPosition(pos);
					break;
				}

			}*/
		}
		else if (type == 5) // chat message received
		{
			std::string receivedMessage;
			receivePacket >> receivedMessage;

			if (!receivedMessage.empty())
			{
				std::string senderName;
				/*for (unsigned int k = 0; k < enemies.size(); k++)
				{
					if (enemies[k]->getID() == id)
						senderName = enemies[k]->getName();
				}*/
				if (id == p->getID())
					senderName = p->getName();
				std::string testMessage(receivedMessage);
				std::string newString = testMessage.substr(0, testMessage.length() - 1);
				m_textMessage = senderName + ":" + newString;
			}


		}
		//Number 6 is reserved by the server for saving the name

		else if (type == 7) //Create new players
		{
			int playerNumber;
			std::vector<std::string> playersName;
			std::vector<int> playersId;
			vector<bool> plMaker;
			receivePacket >> playerNumber;
			std::cout << "Num of players on server: " << playerNumber << std::endl;

			for (int i = 0; i < playerNumber; ++i)
			{
				std::string tempName;
				int tempId;
				bool tempBool;
				UINT tempSocketPtr;
				receivePacket >> tempId;
				receivePacket >> tempName;
				receivePacket >> tempBool;
				playersName.push_back(tempName);
				playersId.push_back(tempId);
				plMaker.push_back(tempBool);
				//we update players later... but now need to create it
			}


			for (unsigned int i = 0; i < playersId.size(); ++i) //loop through id-s we got
			{
				bool haveThatEnemy = false;
				for (unsigned int v = 0; v < playerKidlist.size(); v++) //check if we already have enemy with that id
				{
					if (playerKidlist[v]->playerid == playersId[i])
					{
						haveThatEnemy = true;
					}

				}
				
				if (playersId[i] != p->getID() && !haveThatEnemy) //if it is not our id and if we dont have that enemy, create a new enemy with that id
				{
					auto newkid = make_unique<kid>();
					newkid->createKid("resources/kid.xml", kidSheet, KidSpawn, m_engine, this->m_source, kidDeathSheet, m_engine->GetCam());
					m_engine->Addentity(newkid._Myptr(), 0);
					newkid->playerid = playersId[i];
					//Player(std::unique_ptr<sf::TcpSocket>* socket, kid* KID, Engine* engine, bool maker, int id);
					//std::make_unique<Player> newplayer();
					//TODO
					playerKidlist.push_back(move(newkid));
					m_textMessage = "New player connected: " + playersName[i];
					std::cout << "Created a new player kid with player id: " << playersId[i] << std::endl;

				}
				
			}

			playersName.clear();
			playersId.clear();
			plMaker.clear();

		}
		else if (type == 10)
		{
			//supermaker
			bool b;
			receivePacket >> b;
			if (p->getId() == id)
			{
				p->setPrefix("[SuperMaker]");
				p->SetSuperMaker(b);
				
				//m_engine->SetSuperMaker(b);
			}
		}
		else if (type == 11)
		{
			//maker
			bool b;
			receivePacket >> b;
			if (p->getId() == id)
			{
				p->SetMaker(b);
			}
		}


	}

}