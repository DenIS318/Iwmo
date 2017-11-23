#include "Server.h"

using namespace std;
#define server "[SERVER]: "
Server::Server(Engine* engine,CSource* source)
{
	m_engine = engine;
	m_maxPlayerNumber = 1000;
	m_currentID = 0;
	m_playerNumber = 0;
	m_ls = source;
	m_isRunning = true;
	m_listener.listen(25565);
	m_selector.add(m_listener);
	std::cout << "Server is started. Waiting for connections..." << std::endl;
}

void Server::SetSuperMaker(bool b,int id)
{
	//m_engine->SetSuperMaker(b);
	string s;
	if (b) {
		s = "recieved";
	}	
	else
	{
		s = "lost";
	}
	cout << server << "Client " << m_playerList[id].getName() << " "+s+" SuperMaker rights" << endl;
	Packet sPacket;
	//setsupermaker type
	sPacket << 10;
	//new super maker id
	sPacket << id;
	//boolean
	sPacket << b;
	sendPacket(sPacket);
}
void Server::run()
{
	while (m_isRunning)
	{
		if (m_selector.wait())
		{
			if (m_selector.isReady(m_listener)) // if server is ready to receive new connections
			{
				
				std::unique_ptr<sf::TcpSocket> tempSocket = std::make_unique<sf::TcpSocket>();
				
				if (m_listener.accept(*tempSocket) == sf::Socket::Done)
				{
					if (m_playerNumber < m_maxPlayerNumber) //if server is not full
					{
						
						/*
						on connecting user, creating this player
						*/
						kid* newkid = new kid();
						auto lss = this->m_ls;
						newkid->createKid("resources/kid.xml", kidSheet, KidSpawn, m_engine, lss, kidDeathSheet, m_engine->GetCam());
						if (m_engine->gamestarted)
						{
							//for not creating kids in lobby
							m_engine->Addentity(newkid, 0);
						}
						newkid->playerid = m_currentID;
						m_playerList.emplace_back(Player(&tempSocket,newkid,m_engine,true, m_currentID));
						m_selector.add(*m_playerList.back().getSocket());
						m_playerNumber++;

						sf::Packet outPacket;
						outPacket << 0;
						outPacket << m_currentID;
						sf::TcpSocket* temp = m_playerList[m_currentID].getSocket();
						sf::IpAddress ip = temp->getRemoteAddress();
						unsigned short port = temp->getRemotePort();
						//delete &temp;
						cout << server << "Client " <<  ip << ":" << port << " with id " << m_currentID << " connected!" << endl;
						if (m_playerList.back().getSocket()->send(outPacket) != sf::Socket::Done) //Send client id
							std::cout << server << "error sending player index" << std::endl;
						if (ip.getLocalAddress() == sf::IpAddress::getLocalAddress())
						{
							m_playerList[m_currentID].setName("Server");
							SetSuperMaker(true, m_currentID);
						}
						m_currentID++;
					}
					else //if server is full
					{
						sf::Packet outPacket;
						outPacket << 2;
						outPacket << 0;

						if (tempSocket->send(outPacket) != sf::Socket::Done)
							std::cout << server << "Error sending server is full message" << std::endl;

						std::cout << server << "User tried to connect but the server was full" << std::endl;
					}
				}


			}
			else
			{
				//Receive data
				for (unsigned int i = 0; i < m_playerList.size(); i++)
				{
					if (m_selector.isReady(*m_playerList[i].getSocket()))
					{
						sf::Packet received;
						if (m_playerList[i].getSocket()->receive(received) == sf::Socket::Done)
						{
							m_playerList[i].setTimeout(m_clock.getElapsedTime());

							int num, id;
							received >> num;
							received >> id;


							// 0 is sent when player establishes a connection to the server

							if (num == 1) // player disconnected, send message to all players to delete his character and delete him from servers players list
							{

								sendPacket(received, i);

								for (auto& itr : m_playerList)
								{
									if (itr.getId() == id)
									{

										std::cout << server << std::endl << "Client disconnected!" << std::endl;
										std::cout << server << "ID: " << itr.getId() << " Name: " << itr.getName() << std::endl;
									}
								}


								m_engine->Removeentity(m_playerList[i].GetKid(),0);
								m_selector.remove(*m_playerList[i].getSocket());
								m_playerList.erase(m_playerList.begin() + i);
								m_playerNumber--;
								std::cout << server << "Number of players: " << m_playerNumber << std::endl;
								break;
							}
							//Number 2 means the server is full
							//it is sent only to the player who cannot connect

							else if (num == 3) //Moving direction
							{
								if (id != -1)
								{
									sendPacket(received, i);
								}

							}
							else if (num == 4) //Position
							{
								if (id != -1)
								{
									sendPacket(received, i);
								}
							}
							else if (num == 5) //Send text message
							{
								for (unsigned int k = 0; k < m_playerList.size(); k++)
								{
									sendPacket(received);
									std::string messageSent;
									std::cout << server << "Sent: " << (received >> messageSent) << std::endl;

								}
							}
							else if (num == 6) //Save player name
							{
								if (m_playerList[i].getId() == id)
								{
									std::string nameHolder;
									received >> nameHolder;
									m_playerList[i].setName(nameHolder);
									std::cout << server << "New client added." << std::endl;
									std::cout << server << "ID: " << id << " Name: " << nameHolder << std::endl;
									std::cout << server << "Number of players: " << m_playerNumber << std::endl;
								}
							}
							else if (num == 7) //send client list with id and names  When player recive this it goes through the list and compares it with its list, if he finds a number that he doesn't have he creates a enemy with that id
							{
								sf::Packet namePacket;
								namePacket << 7;
								namePacket << 0;
								namePacket << m_playerNumber;

								for (unsigned int j = 0; j < m_playerList.size(); ++j)
								{
									namePacket << m_playerList[j].getId();
									namePacket << m_playerList[j].getName();
									namePacket << m_playerList[j].GetMaker();
								}

								sendPacket(namePacket);
							}
							//num 10 not here. see setsupermaker above
							else if (num == 11)
							{
								//maker
								bool makerr;
								received >> makerr;
								m_playerList[id].SetMaker(makerr);
								sf::Packet makerPacket;
								makerPacket << 7;
								makerPacket << id;
								makerPacket << makerr;
								sendPacket(makerPacket);
							}
							
							

						}



						//If some player time-out-ed alert other players
						float tempTime = m_clock.getElapsedTime().asSeconds() - m_playerList[i].getTimeout().asSeconds();
						if (tempTime >= 5)
						{
							sf::Packet timeOutPacket;
							timeOutPacket << 2;
							timeOutPacket << m_playerList[i].getId();

							std::cout << server << "Player: " << m_playerList[i].getId() << " timeouted" << std::endl;
							sendPacket(received, i);

							m_selector.remove(*m_playerList[i].getSocket());
							m_playerList.erase(m_playerList.begin() + i);
							m_playerNumber--;
							break;
						}
					} // end of player socket is ready
				}
			}
		}

	}
}



void Server::sendPacket(sf::Packet & packet, unsigned int skip)
{
	for (unsigned int i = 0; i < m_playerList.size(); ++i)
	{
		if (skip == i)
			continue;
		if (m_playerList[i].getSocket()->send(packet) != sf::Socket::Done)
		{
			std::cout << server << "Error sending packet in sendPacket func" << std::endl;
		}
	}
}