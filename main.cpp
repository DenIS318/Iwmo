#include <SFML\Graphics.hpp>



//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
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
sf::Font font;
sf::TcpSocket socket;
sf::SocketSelector selector;
bool connected = false;
bool serverrunning = false;
inline void enablebox()
{
	ip = "";
	iptext.setString(ip);
	ipbox.setState(Enabled);
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

		return;

	}
}

inline void emplaceBlock(Engine* engine,Vector2f point,int selectedlayer)
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
inline void emplaceBlock(Engine* engine, Vector2f point)
{
	emplaceBlock(engine, point, engine->selectedlayer);
}
inline void checkevent(Event event, RenderWindow* window, Engine* engine)
{
	if (engine != NULL)
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
						if (engine->ShowImgui)
						{

							Vector2f cursorpos = Vector2f(event.mouseMove.x, event.mouseMove.y);
							Vector2f winsize = engine->imguisize;
							Vector2f winpos = engine->imguipos;
							FloatRect ImGuiRect(winpos, winsize);
							if (!ImGuiRect.contains(cursorpos))
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
						}

						if (engine->selectedblock != NULL)
						{

							if (!engine->ImGuifocus)
							{

								Vector2i pos(event.mouseMove.x, event.mouseMove.y);
								auto newpos = engine->GetWindow()->mapPixelToCoords(pos);
								if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
								{
									int x = newpos.x;
									int y = newpos.y;
									newpos.x = (x / engine->GridSize.x) * engine->GridSize.x;
									newpos.y = (y / engine->GridSize.y) * engine->GridSize.y;
								}
								else
								{
									auto b = engine->selectedblock->getGlobalBounds();
									auto sizedivide2 = Vector2i(b.width / 2, b.height / 2);
									newpos -= Vector2f(sizedivide2);
								}
								engine->selectedblock->setPosition(newpos);
							}
						}
						if (Keyboard::isKeyPressed(Keyboard::LShift) && Mouse::isButtonPressed(sf::Mouse::Button::Left))
						{
							if (engine->blockprototype != NULL)
							{
								if (!engine->ImGuifocus)
								{
									auto newpos = engine->selectedblock->getPosition();
									auto b = engine->selectedblock->getGlobalBounds();
									auto sizedivide2 = Vector2i(b.width / 2, b.height / 2);
									newpos += Vector2f(sizedivide2);
									engine->blockprototype->sprite.setPosition(newpos);
									emplaceBlock(engine, newpos);
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
		case sf::Event::MouseButtonPressed:
			if (engine->ClientIsMaker)
			{
				if (event.mouseButton.button == Mouse::Button::Left)
				{
					if (gamestarted)
					{
						if (engine->blockprototype != NULL)
						{
							if (!engine->ImGuifocus)
							{
								auto newpos = engine->selectedblock->getPosition();
								auto b = engine->selectedblock->getGlobalBounds();
								auto sizedivide2 = Vector2i(b.width / 2, b.height / 2);
								newpos += Vector2f(sizedivide2);
								engine->blockprototype->sprite.setPosition(newpos);
								emplaceBlock(engine, newpos);
							}
						}

					}
				}
			}

			if (!gamestarted)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i position = sf::Mouse::getPosition(*window);
					if (kidrect.contains(position))
					{
						if (ipbox.getState() != myState::Enabled)
						{
							enablebox();
						}

					}
					else if (makerrect.contains(position))
					{

						if (ipbox.getState() != myState::Enabled)
						{
							enablebox();
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

								thread thr = thread(&beginconnect, true, temp, window, engine);

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
					if (event.key.code == Keyboard::Tab)
					{
						ImGui::SetWindowCollapsed("Maker", !engine->ImguiCollappsed);
					}
				}
			}
			break;
		case Event::TextEntered:
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
			break;
		default:
			break;
		}
	
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
//MAIN
int main()
{

	font.loadFromFile("resources/Arial.otf");
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
	iptext.setFont(font);
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

		continuepool(window, &engine);
		engine.Render();
	}
	ImGui::SFML::Shutdown();
	return EXIT_SUCCESS;
}