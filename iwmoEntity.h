#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
//#include "MyEntityEngine.h"
#include "tinyxml\tinyxml.h"


using namespace sf;
using namespace std;

class iwmoEntity
{
public:
	iwmoEntity();
	void setPos(Vector2f);
	void m_move(int, int);
	void initEntit(std::string fileName, Texture* t);
	~iwmoEntity();
	void draw(RenderWindow*);
	int GetX();
	int GetY();
	AnimationManager anim;
	inline void MGetEvent(Event);
	AnimationManager* GetTextureAnimation();
	iwmoEntity* MGetBase();
	//MyEntityEngine* eng = new MyEntityEngine;
	//void SettingHandler(GameHandler* h);
private:
	int x = 0;
	int y = 0;

};

