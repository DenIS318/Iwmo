#include <SFML\Graphics.hpp>
#include "mytextbox.h"
#include <SFML/Network.hpp>
#include "Server.h"
#include "Network.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include "Game.h"
using namespace std;
using namespace myState;
CSource* source = new CSource;

/*const unsigned short maxPlayerNumber = 20;
unsigned short playerNumber = 0;*/
Texture kidbuttext, makerbuttext, startt, serverr;
Sprite kidbut, makerbut, start, server;
std::unique_ptr<Network> network;
sf::IntRect kidrect(200, 381, 70, 40);
sf::IntRect makerrect(600 - 105, 381, 105, 40);
sf::IntRect startrect(280 + 70, 500, 88, 40);
sf::IntRect boxrect(startrect.left - 60, startrect.top - 50, 200, 20);
sf::IntRect serverrect(650, 500, 104, 40);
mytextbox ipbox(sf::Vector2f(200, 20));
static string ip;
bool ready = false;
sf::Text iptext;
static Game* game;
bool gamestarted = false;
#define mainlayer 0
#define bgmainlayer 1
#define textlayer 2
#define isclient iskid
#define socket sockett
bool allow = false;
bool serverstarted = false;
bool isclient = true;
sf::TcpSocket socket;
sf::SocketSelector selector;
bool connected = false;
bool serverrunning = false;
bool KID = false;
inline void enablebox()
{
	ip = "";
	iptext.setString(ip);
	ipbox.setState(Enabled);
	ipbox.setOutlineThickness(2);
	ipbox.setOutlineColor(Color::Black);
	iptext.setFillColor(Color::Black);

}

inline void beginbind(IpAddress address, RenderWindow* window)
{
	Server serv;
	serv.run();

}

void startgame(Engine* engine, RenderWindow* window)
{
	game = new Game(engine, window, source);
	gamestarted = true;
	engine->listboxvectorFilters = game->Filters;

}
inline void beginconnect(bool kid, IpAddress address, RenderWindow* window, Engine* engine)
{

	if (!connected)
	{
		connected = true;
		iskid = kid;
		try {
			network = std::make_unique<Network>(address, (unsigned short)port);
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			return;
		}
		ready = true;
		engine->ClientIsMaker = !kid;
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
						
						if (Keyboard::isKeyPressed(HotkeyFastBuild) )
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
						if (ipbox.getState() != myState::Enabled)
						{
							enablebox();
							KID = true;
						}

					}
					else if (makerrect.contains(position))
					{

						if (ipbox.getState() != myState::Enabled)
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
							thread thr(&beginbind, IpAddress::getLocalAddress(), window);
							thr.detach();
						}
						else {
							cout << "Server already started!" << endl;
						}
					}
					else if (startrect.contains(position))
					{
						if (ipbox.getState() == Enabled)
						{
							try {
								char temp[20];


								strcpy_s(temp, ip.c_str());
								inet_addr(temp);
								stoi(temp);

								thread thr = thread(&beginconnect, KID, temp, window, engine);

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
			
			if (!gamestarted)
			{
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (sizeof(ip) > 0 && ip != "")
					{

						ip.pop_back();
						iptext.setString(ip);

					}

				}
			}
			else
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
			break;
		case Event::TextEntered:
			if (!gamestarted)
			{
				if (ipbox.getState() == Enabled)
				{
					if (event.text.unicode >= 46 && event.text.unicode <= 57 && event.text.unicode != 47)
					{
						ip.push_back((char)event.text.unicode);
						iptext.setString(ip);
						if (debug)
						{

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
		checkevent(event, window, engine);
	}
}
float angleBetween(const Vector2f &v1, const Vector2f &v2)
{
	return  atan2(v2.y, v2.x) - atan2(v1.y, v1.x);
}
//MAIN
int main()
{
	static Engine engine;
	engine.init(Width, Height, WindowName, framerate);
	Texture text;
	RenderWindow* window = engine.GetWindow();
	engine.AddLayer();
	engine.AddLayer();
	engine.AddLayer();
	text.loadFromFile("resources/bg.jpg");
	Sprite bgmain;
	bgmain.setTextureRect(sf::IntRect(0, 0, Width, Height));
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
	ipbox.setPosition(startrect.left - 60, startrect.top - 50);
	//
	kidrect = (IntRect)kidbut.getGlobalBounds();
	serverrect = (IntRect)server.getGlobalBounds();
	makerrect = (IntRect)makerbut.getGlobalBounds();
	startrect = (IntRect)start.getGlobalBounds();
	//
	iptext.setCharacterSize(12);
	iptext.setFont(engine.font);
	iptext.setFillColor(Color::Black);
	iptext.setPosition(ipbox.getPosition().x + 5, ipbox.getPosition().y + 2);
	//
	if (debug)
	{
		//printf("Address of pSource is %p\n", (void *)source);
	}
	if (!allow)
	{
		iptext.setFillColor(sf::Color::Transparent);
		ipbox.setState(myState::Disabled);
	}
	//adding
	
	engine.AddSprite(&bgmain, 0);
	engine.AddSprite(&kidbut, 0);
	engine.AddSprite(&makerbut, 0);
	engine.AddSprite(&start, 0);
	engine.AddSprite(&ipbox, 0);
	engine.AddSprite(&iptext, 1);
	engine.AddSprite(&server, 0);
	//
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
		if (engine.FreeCamera && gamestarted && engine.ClientIsMaker)
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
				/*float angleRadians = atan2(insideOrigin.y - cursorpos.y, insideOrigin.x - cursorpos.x);
				auto angle = angleRadians * 180 / IWMOPHIE;*/
				auto angle = angleBetween(insideOrigin, Vector2f(cursorpos));
				/*
				auto x = cos(sprite()->getRotation()*IWMOPHIE / 180) * bulletspeedratio;
				auto y = sin(sprite()->getRotation()*IWMOPHIE / 180) * bulletspeedratio;
				*/
				cout << angle << endl;
				auto x = cos(angle) * engine.Scrollingratio.x;
				auto y = sin(angle) * engine.Scrollingratio.y;
				cam->move(Vector2f(x, y));
			}
		}
		continuepool(window, &engine);
		engine.Render();
	}
	ImGui::SFML::Shutdown();
	return EXIT_SUCCESS;
}