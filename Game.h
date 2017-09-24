#pragma once
#ifndef GAME_H
#define GAME_H
//#include "IwmoConfig.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MyListener.h"
#include <tmx\MapLayer.hpp>
#include "Animation.h"
#include "kid.h"
#include "Engine.h"
//#include "Player.h"
#include "tmx\Log.hpp"

using namespace std;
using namespace sf;
using namespace tmx;
using namespace IV;
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
	Game(Engine*, RenderWindow*);
	~Game();
	void StartGame(Engine* engine);
	/*
	Sending event source and handler to Game, yeap, perfect explanation
	*/
	void EventHandling(CSource* sourc);


	virtual void m_hookEvent(CSource* pSource);
	virtual void m_unhookEvent(CSource* pSource);
	View* GetCam();
	Game* getGame();
	const Vector2f CAM_SIZE = Vector2f(800, 600);
	const Vector2f CAM_CENTER = Vector2f(CAM_SIZE.x/2, 3200-(CAM_SIZE.y/2));
	RenderWindow* window;
	RenderWindow* Getwindow();

	sf::View camera;
	CSource* m_ls;
private:
	TiXmlDocument kidXML;
	TiXmlDocument LevelXML;
	Texture* kidSheet = new Texture;
};
#endif