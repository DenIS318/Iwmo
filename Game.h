#pragma once

//#include "IwmoConfig.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MyListener.h"
#include "Animation.h"
#include "kid.h"
#include "Engine.h"
#include "Block.h"
#include <boost/filesystem.hpp>
#include <boost/any.hpp>
using namespace boost::filesystem;
using namespace std;
using namespace sf;
using namespace Iwmo;
class Game
{

public:

	/*static Game* GInstance()
	{
	// ñîãëàñíî ñòàíäàðòó, ýòîò êîä ëåíèâûé è ïîòîêîáåçîïàñíûé
	static Game s;
	return &s;
	}*/
	Game();
	/*
	Initalizates games with engine.
	*/
	Game(Engine*, RenderWindow*,CSource*);
	~Game();
	void StartGame(Engine* engine,CSource*);
	//void EventHandling(CSource* sourc);
	Music castleent;

	virtual void m_hookEvent(CSource* pSource);
	virtual void m_unhookEvent(CSource* pSource);
	View* GetCam();
	Game* getGame();
	void INITMAP();
	const sf::Vector2f CAM_SIZE = sf::Vector2f(800, 600);
	const sf::Vector2f CAM_CENTER = sf::Vector2f(CAM_SIZE.x/2, 3200-(CAM_SIZE.y/2));
	RenderWindow* window;
	RenderWindow* Getwindow();
	Engine* m_engine;
    sf::View camera;
	CSource* m_ls;
	/*
	Creates block with given name in blocks folder without dot
	*/
	Block CreateBlockByName(string name);
	/*
	Get block texture* with given name in blocks folder with extension
	*/
	Texture* GetBlockTextureByName(string name);
	vector<IwmoBlock>* GetBlockList();
	
	 sf::Texture* kidDeathSheet = new Texture;
	 sf::Texture* kidSheet = new Texture;
private:
	void LS();
	/*
	Avivable filters:
	solids
	decorations
	traps
	animated
	*/
	void InitIwmoBlocks(string filter);
	void AddIwmoBlock(string name, BlockType blocktype);
	void LoadSheets();
	TiXmlDocument kidXML;
//	TiXmlDocument kidDeathXML;
	TiXmlDocument LevelXML;
	//Texture* kidSheet = new Texture;
	//Texture* kidDeathSheet = new Texture;

	 vector<IwmoBlock> IwmoBlocks;
};
[event_receiver(native)]
class GameHandler : public Game
{

public:
	void OnCustomEvent(CustomEvent* event);
	GameHandler();
	GameHandler(const Game*);
	~GameHandler();
	Event event;
	Game* gameinstance;
	RenderWindow* windinst = Game::Getwindow();
	Event GameHandler::GetEvent()
	{
		return event;

	}
	void m_hookEvent(CSource* pSource);

	void m_unhookEvent(CSource* pSource);
private:
	View* camerapointer = gameinstance->GetCam();
	void GameHandler::OnEvent(Event eventt);
};