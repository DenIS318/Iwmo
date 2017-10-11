#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
//#include "MyEntityEngine.h"
#include "tinyxml\tinyxml.h"
#include "MyListener.h"

//#include "Game.h"
 // !GAME_H
enum EntityState {
	idle,
	walk,
	jump,
	fall,
	slide,
	channel,
	death,
	unknown
};

using namespace sf;
using namespace std;

class iwmoEntity
{
public:
	iwmoEntity();
	void setPos(Vector2f);
	void m_move(int x, int y);
	void initEntit(std::string fileName, Texture* t);
	~iwmoEntity();
	void draw(RenderWindow*);
	float GetX();
	float GetY();
	Vector2f GetPos();
	AnimationManager anim;
	virtual void MGetEvent(Event);
	virtual void control();
	AnimationManager* GetTextureAnimation();
	iwmoEntity* MGetBase();
	float SpeedX = 50.0;
	float SpeedY = 70.0;
	EntityState state = unknown;
	void updatetime(float t);
	float time=0.0;
	void GetEventSource(CSource* sourc);
	CSource* m_souc;
	bool visible = true;
private:
	float x = 0;
	float y = 0;
	
};

