#include <SFML\Graphics.hpp>
#include "mytextbox.h"
#include <SFML/Network.hpp>
#include "Server.h"
#include "Network.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include "TexturePreloader.h"
#include "Game.h"
using namespace std;
using namespace myState;
CSource* source = new CSource;
Texture kidbuttext, makerbuttext, startt, serverr;
Sprite kidbut, makerbut, start, server;
std::unique_ptr<Network> network;
sf::IntRect kidrect(200, 381, 70, 40);
sf::IntRect makerrect(600 - 105, 381, 105, 40);
sf::IntRect startrect(280 + 70, 500, 88, 40);
sf::IntRect boxrect(startrect.left - 60, startrect.top - 50, 200, 20);
sf::IntRect serverrect(650, 500, 104, 40);
mytextbox* ipbox = NULL;
mytextbox* namebox = NULL;
string myname;
string ip;
Text* iptext = new Text();
Text* nametext = new Text();
Server* myserv;
bool ready = false;
static Game* game;
bool gamestarted = false;
#define mainlayer 0
#define bgmainlayer 1
#define textlayer 2
bool serverstarted = false;
//bool isclient = true;
//sf::TcpSocket socket;
//sf::SocketSelector selector;
bool connected = false;
bool serverrunning = false;
bool KID = false;
inline void enablebox()
{
	ip = "";
	myname = "";
	ipbox->setVisible(true);
	namebox->setVisible(true);
	ipbox->AllowAutoEnable = true;
	namebox->AllowAutoEnable = true;
	ipbox->showText(true);
	namebox->showText(true);
	nametext->setString(NameStringHelp);
	iptext->setString(IpStringHelp);

}

inline void beginbind(Engine* engine)
{
	Server serv(engine,source);
	serv.run();
	myserv = &serv;

}
inline void Recieve()
{
	if (network != NULL)
	{
		network->receive(myplayer);
	}
	else if (mynetwork != NULL)
	{
		mynetwork->receive(myplayer);
	}
	this_thread::sleep_for(chrono::microseconds(1));
	Recieve();
}
void startgame(Engine* engine, RenderWindow* window)
{
	if (!gamestarted)
	{
		game = new Game(engine, window, source);
		gamestarted = true;
		engine->listboxvectorFilters = game->Filters;;
		//engine->removeTextBox(&ipbox);
		//engine->removeTextBox(&namebox);
		//engine->RemoveText(nametext);
		//engine->RemoveText(iptext);
	}

}
inline void beginconnect(bool _kid, IpAddress address,  Engine* engine)
{

	if (!connected)
	{
		connected = true;
		engine->ClientIsMaker = !_kid;
		MyName = myname;
		try {
			static auto newplayer = new Player();
			kid* mykid = new kid();
			mykid->yourkid = true;
			mykid->createKid("resources/kid.xml", kidSheet, KidSpawn, engine, source, kidDeathSheet, engine->GetCam());
			engine->Addentity(mykid, 0);
			auto nullval = engine->ClientKid();
			nullval = mykid;
			newplayer->SetKid(mykid);
			newplayer->setName(MyName);
			myplayer = newplayer;
			network = std::make_unique<Network>(address,engine,source, (unsigned short)port);
			mynetwork = network.release();
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			connected = false;
			return;
		}
		
		ready = true;
		return;

	}
}

inline void emplaceBlock(Engine* engine,Vector2f point,int selectedlayer)
{
	if (engine->make)
	{
		if (selectedlayer < 0)
		{
			selectedlayer = 0;
		}
		//get block at this point with selected layer
		auto B = engine->GetBlockAtPoint(point, selectedlayer);
		if (B == NULL)
		{
			B = new Block(*engine->blockprototype);
			engine->AddBlock(B, selectedlayer);
		}
		else
		{
			if (engine->lastemplacedblockpos != point)
			{
				engine->RemoveBlock(B);
				B = new Block(*engine->blockprototype);

				engine->AddBlock(B, selectedlayer);
				engine->lastemplacedblockpos = point;
			}
		}
	}
	
}
inline void emplaceBlock(Engine* engine, Vector2f point)
{
	emplaceBlock(engine, point, engine->selectedlayer);
}
inline void checkevent(Event event, RenderWindow* window, Engine* engine)
{

		switch (event.type)
		{
		case Event::MouseMoved:
		{

			if (gamestarted)
			{
				if (engine->GetWindow()->hasFocus())
				{
					if (engine->ClientIsMaker)
					{
						Vector2i cursorpos = Mouse::getPosition(*engine->GetWindow());
						Vector2f winsize = engine->imguisize;
						Vector2f winpos = engine->imguipos;
						FloatRect ImGuiRect(winpos, winsize);
						
							if (!ImGuiRect.contains(Vector2f(cursorpos)))
							{
								engine->ImGuifocus = false;
							}
							else
							{
								engine->ImGuifocus = true;
								if (engine->lastemplacedblockpos != Vector2f(-666, -666))
								{
									engine->lastemplacedblockpos = Vector2f(-666, -666);
								}
							}
						if (!engine->ImGuifocus)
						{
							
							if (engine->blockprototype!= NULL)
							{
								
								engine->blockprototype->sprite.setPosition(engine->mouseboundsshow.getPosition());
							}
							if (engine->textprototype != NULL)
							{
								engine->textprototype->setPosition(engine->mouseboundsshow.getPosition());
							}
							
						}
						if(HotkeyFastBuild)
						{ 
						
							if (Mouse::isButtonPressed(sf::Mouse::Button::Left))
							{
								if (engine->blockprototype != NULL)
								{
									if (!engine->ImGuifocus)
									{
										emplaceBlock(engine, engine->blockprototype->sprite.getPosition(),engine->selectedlayer);
									}
								}
							}
							else if (Mouse::isButtonPressed(sf::Mouse::Button::Right))
							{
								if (!engine->ImGuifocus)
								{
									if (engine->make)
									{
										auto blvec = engine->GetBlocksAtRect(engine->mouseboundsshow, engine->selectedlayer);
										if (!blvec.empty())
										{
											for (auto it = blvec.begin(); it != blvec.end(); ++it)
											{
												auto val = *it._Ptr;

												engine->RemoveBlock(val, engine->selectedlayer);

											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		break;
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			kidrect = IntRect(kidbut.getGlobalBounds());
			makerrect = IntRect(makerbut.getGlobalBounds());
			serverrect = IntRect(server.getGlobalBounds());
			startrect = IntRect(start.getGlobalBounds());
			namebox->setPosition(startrect.left - 60, startrect.top - 270);
			nametext->setPosition(namebox->getPosition() + Vector2f(0, -35));
			ipbox->setPosition(namebox->getPosition().x, namebox->getPosition().y + 80);
			iptext->setPosition(ipbox->getPosition() + Vector2f(0, -35));
			break;
		case sf::Event::MouseButtonPressed:
			if (engine->ClientIsMaker)
			{
				if (event.mouseButton.button == Mouse::Button::Left)
				{
					if (gamestarted)
					{
						if(engine->blockprototype == NULL)
						{
							
								auto blvec = engine->GetBlocksAtRect(engine->mouseboundsshow, engine->selectedlayer);
								if (!blvec.empty())
								{
									auto mpos = blvec.size() - 1;
									auto bl = blvec[mpos];
									engine->blockprototype = bl;
									engine->BlockListSelectBlock(engine->blockprototype);
								}
							
							
						}
						if (!engine->ImGuifocus)
						{
							if (engine->blockprototype != NULL)
							{
								
								emplaceBlock(engine, engine->blockprototype->sprite.getPosition(), engine->selectedlayer);
							}
							if (engine->textprototype != NULL)
							{
								engine->AddText(new Text(*engine->textprototype));
							}
						}

					}
				}
				else if (event.mouseButton.button == Mouse::Button::Right)
				{
					if (gamestarted)
					{
							if (!engine->ImGuifocus)
							{
								if (engine->make)
								{
									auto blvec = engine->GetTextAtRect(engine->mouseboundsshow);
									if (!blvec.empty())
									{
										for (auto it = blvec.begin(); it != blvec.end(); ++it)
										{
											auto val = *it._Ptr;
											engine->RemoveText(val);
										}
									}
									auto blvec2 = engine->GetBlocksAtRect(engine->mouseboundsshow,engine->selectedlayer);
									if (!blvec2.empty())
									{
										for (auto it = blvec2.begin(); it != blvec2.end(); ++it)
										{
											auto val = *it._Ptr;
											engine->RemoveBlock(val);
										}
									}
								}
							}

					}
				}
			}

			if (!gamestarted)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i position = Vector2i(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
					if (kidrect.contains(position))
					{
						if (ipbox->getState() != myState::Enabled)
						{
							enablebox();
							KID = true;
						}

					}
					else if (makerrect.contains(position))
					{

						if (ipbox->getState() != myState::Enabled)
						{
							enablebox();
							KID = false;
						}



					}
					else if (serverrect.contains(position))
					{
						if (!serverstarted)
						{
							serverstarted = true;
							thread thr(&beginbind, engine);
							thr.detach();
						}
						else {
							cout << "Server already started!" << endl;
						}
					}
					else if (startrect.contains(position))
					{
						if (ip.size() > 0)
						{
							try {
								char temp[20];


								strcpy_s(temp, ip.c_str());
								inet_addr(temp);
								stoi(temp);

								thread thr = thread(&beginconnect, KID, temp, engine);

								thr.detach();
								while (!ready) {             // wait until main() sets ready...
									std::this_thread::yield();
								}
								startgame(engine, window);

							}
							catch (exception e)
							{
								cout << e.what() << endl;
							}
						}
					}
				}
			}
			break;
		case sf::Event::KeyPressed:
			{
			if (gamestarted)
			{
				if (engine->ClientIsMaker)
				{

					if (event.key.code == HotkeyDelete)
					{
						if (engine->blockprototype != NULL)
						{
							delete engine->blockprototype;
							engine->blockprototype = NULL;
						}
						if (engine->textprototype != NULL)
						{
							delete engine->textprototype;
							engine->textprototype = NULL;
						}
					}
					if (event.key.code == HotkeyListener)
					{
						auto mousepos = sf::Mouse::getPosition(*engine->GetWindow());
						Vector2f pos = engine->GetWindow()->mapPixelToCoords(mousepos);
						engine->setListenerPosition(Vector3f(pos.x, pos.y, 0));
					}
					if (event.key.code == HotkeyTeleportMusic)
					{
						auto mousepos = sf::Mouse::getPosition(*engine->GetWindow());
						Vector2f pos = engine->GetWindow()->mapPixelToCoords(mousepos);
						engine->CurrentMusic->setPosition(Vector3f(pos.x, pos.y, 0));
						engine->MusicSprites.at(engine->FindMusicPtr(engine->CurrentMusic))->setPosition(pos);
					}
					if (event.key.code == HotkeyImGui)
					{
						ImGui::SetWindowCollapsed("Maker", !engine->ImguiCollappsed);
					}
					else if (event.key.code == HotkeyFlip)
					{
						if (engine->blockprototype != NULL && !engine->ImGuifocus)
						{
							engine->FlipBlock(engine->blockprototype);
						}
					}
				}
			}
			}
			break;
		case Event::MouseWheelScrolled:
			if (gamestarted)
			{
				if (!engine->ImGuifocus)
				{
					if (engine->blockprototype != NULL)
					{
						auto rotation = engine->blockprototype->sprite.getRotation();
						auto value = rotation + event.mouseWheelScroll.delta * 15;
						engine->blockprototype->sprite.setRotation(value);
					}
					if (engine->textprototype != NULL)
					{
						auto rotation = engine->textprototype->getRotation();
						auto value = rotation + event.mouseWheelScroll.delta * 15;
						engine->textprototype->setRotation(value);
					}
				}
			}
			break;
		default:
			break;
		}
	
	}

inline void continuepool(RenderWindow* window, Engine* engine)
{
	Event event;
	while (window->pollEvent(event))
	{
		__raise (*source).OnEvent(event);
		ImGui::SFML::ProcessEvent(event);
		if (namebox != NULL)
		{
			namebox->GetEvent(event);
			ipbox->GetEvent(event);
		}
		checkevent(event, window, engine);
	}
	
}
float angleBetween(const Vector2f &v1, const Vector2f &v2)
{
	float radians = atan2(v1.y - v2.y, v1.x - v2.x);
	return radians * 180 / IWMOPHIE; // in degress
}
void soundpreload(Engine* m_engine)
{
	m_engine->AddSoundBuffer("kidjump");
	m_engine->LoadSound("jump1.ogg", "kidjump");
	m_engine->AddSoundBuffer("kiddoublejump");
	m_engine->LoadSound("jump2.ogg", "kiddoublejump");
	m_engine->AddSoundBuffer("kiddeath");
	m_engine->LoadSound("death.ogg", "kiddeath");
	m_engine->AddSoundBuffer("kidfire");
	m_engine->LoadSound("bullet.flac", "kidfire");
}
//MAIN
int main()
{
	TexturePreloader preloader;
	preloader.Preload();
	static Engine engine;
	engine.init(Width, Height, WindowName, framerate);
	soundpreload(&engine);
	ipbox = new mytextbox(Vector2f(200, 20), &ip, &engine.font, engine.GetWindow());
	namebox = new mytextbox(Vector2f(200, 20), &myname, &engine.font, engine.GetWindow());
	ipbox->filter = mytextbox::textboxFilters::ip;
	ipbox->setVisible(false);
	namebox->setVisible(false);
	ipbox->showText(false);
	ipbox->AllowAutoEnable = false;
	namebox->showText(false);
	namebox->AllowAutoEnable = false;
	Texture text;
	RenderWindow* window = engine.GetWindow();
	engine.AddLayer();
	engine.AddLayer();
	engine.AddLayer();
	text.loadFromFile("resources/bg.jpg");
	Sprite bgmain;
	bgmain.setTexture(text);
	//creating
	kidbuttext.loadFromFile(res + but + "kid.png");
	makerbuttext.loadFromFile(res + but + "maker.png");
	serverr.loadFromFile(res + but + "server.png");
	kidbut.setTexture(kidbuttext);
	makerbut.setTexture(makerbuttext);
	server.setTexture(serverr);
	startt.loadFromFile(res + but + "start.png");
	start.setTexture(startt);
	//setting
	kidbut.setPosition(kidrect.left, kidrect.top);
	//
	server.setPosition(serverrect.left, serverrect.top);
	//
	makerbut.setPosition(makerrect.left, makerrect.top);
	//
	start.setPosition(startrect.left, startrect.top);
	//
	nametext->setFont(engine.font);
	nametext->setCharacterSize(22);
	namebox->setPosition(startrect.left - 60, startrect.top - 270);
	nametext->setPosition(namebox->getPosition() + Vector2f(0, -35));
	nametext->setColor(Color::Red);
	engine.AddText(nametext);
	//
	iptext->setFont(engine.font);
	iptext->setCharacterSize(22);
	ipbox->setPosition(namebox->getPosition().x, namebox->getPosition().y + 80);
	iptext->setPosition(ipbox->getPosition() + Vector2f(0, -35));
	iptext->setColor(Color::Red);
	//
	kidrect = (IntRect)kidbut.getGlobalBounds();
	serverrect = (IntRect)server.getGlobalBounds();
	makerrect = (IntRect)makerbut.getGlobalBounds();
	startrect = (IntRect)start.getGlobalBounds();
	//
	//adding
	//
	engine.AddSprite(&bgmain, 0);
	engine.AddSprite(&kidbut, 0);
	engine.AddSprite(&makerbut, 0);
	engine.AddSprite(&start, 0);
	engine.addTextBox(ipbox);
	engine.addTextBox(namebox);
	engine.AddText(iptext);
	engine.AddText(nametext);
//	engine.AddSprite(&iptext, 1);
	engine.AddSprite(&server, 0);
	//
	thread Recthr(&Recieve);
	Recthr.detach();
	while (window->isOpen())
	{
		if (gamestarted)
		{
			auto cam = engine.GetCam();
			if (cam != NULL)
			{
				
				if (engine.FreeCamera && engine.ClientIsMaker && window->hasFocus())
				{
					Vector2f offset;
					if (Keyboard::isKeyPressed(HotkeyScrollUp))
					{
						offset = offset + Vector2f(0, -engine.Scrollingratio.y);
					}
					if (Keyboard::isKeyPressed(HotkeyScrollLeft))
					{
						offset = offset + Vector2f(-engine.Scrollingratio.x, 0);
					}
					if (Keyboard::isKeyPressed(HotkeyScrollDown))
					{
						offset = offset + Vector2f(0, engine.Scrollingratio.y);
					}
					if (Keyboard::isKeyPressed(HotkeyScrollRight))
					{
						offset = offset + Vector2f(engine.Scrollingratio.x, 0);
					}
					cam->setCenter(cam->getCenter() + offset);
				}
				if (cam->getCenter().x < Width / 2)
				{
					cam->setCenter(Vector2f(Width / 2, cam->getCenter().y));
				}
				if (cam->getCenter().y < Height / 2)
				{
					cam->setCenter(Vector2f(cam->getCenter().x, Height / 2));
				}
			}
		}
		if (engine.KeepMouse && gamestarted && engine.ClientIsMaker )
		{
			auto w = engine.GetWindow();
			int maxX = w->getSize().x;
			int maxY = w->getSize().y;

			int mX = sf::Mouse::getPosition(*w).x;
			int mY = sf::Mouse::getPosition(*w).y;

			if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
			{
				if (mX < 0)
					mX = 0;
				else if (mX > maxX)
					mX = maxX;

				if (mY < 0)
					mY = 0;
				else if (mY > maxY)
					mY = maxY;

				sf::Mouse::setPosition(sf::Vector2i(mX, mY), *w);
			}
		}
		if (engine.FreeCamera && gamestarted && engine.ClientIsMaker && engine.GetWindow()->hasFocus())
		{
			Vector2i cursorpos = Mouse::getPosition(*engine.GetWindow());
			auto newpos = engine.GetWindow()->mapPixelToCoords(Vector2i(cursorpos));
			auto cam = engine.GetCam();
			Vector2f offset(20, 20);
			Vector2f insidesize = cam->getSize() - offset;
			FloatRect inside(cam->getCenter() - Vector2f(Width / 2, Height / 2) + Vector2f(offset.x / 2, offset.y / 2), insidesize);
			if (!inside.contains(newpos))
			{
				
				Vector2f insideOrigin(inside.left + inside.width / 2, inside.top + inside.height / 2);
				auto angle = angleBetween(insideOrigin, window->mapPixelToCoords(Vector2i(cursorpos)));
				auto x = cos(angle * IWMOPHIE / 180) * engine.Scrollingratio.x;
				auto y = sin(angle * IWMOPHIE / 180) * engine.Scrollingratio.y;
				cam->move(Vector2f(-x, -y)); // -x and -y, otherwise opposite angle will be
			}
		}
		continuepool(window, &engine);
		engine.Render();
	}
	if (myplayer != NULL)
	{
		if (network != NULL)
		{
			network->disconnect(myplayer);
		}
		else if (mynetwork != NULL)
		{
			mynetwork->disconnect(myplayer);
		}
	}
	if (myserv != NULL)
	{
		myserv->close();
	}
	ImGui::SFML::Shutdown();
	return EXIT_SUCCESS;
}