#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
//#include "MyEntityEngine.h"
#include "tinyxml\tinyxml.h"


//#include "Game.h"
 // !GAME_H
enum EntityState {
	idle,
	walk,
	jump,
	fall,
	slide,
	channel,
	unknown
};

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
	Vector2f GetPos();
	AnimationManager anim;
	virtual void MGetEvent(Event);
	virtual void control();
	AnimationManager* GetTextureAnimation();
	iwmoEntity* MGetBase();
	float SpeedX = 50.0;
	float SpeedY = 50.0;
	EntityState state = unknown;
	void updatetime(float t);
	float time=0.0;
	//TODO 2
	//MyEntityEngine* eng = new MyEntityEngine;
	//void SettingHandler(GameHandler* h);
private:
	int x = 0;
	int y = 0;

};

