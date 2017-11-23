#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "tinyxml\tinyxml.h"
#include "MyListener.h"
#include "IwmoMath.h"
#include "IwmoConfig.h"
#include "Block.h"
#include "Bullet.h"
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
using namespace Iwmo;
class iwmoEntity
{
public:
	iwmoEntity();
	void setPos(Vector2f);
	void m_move(int x, int y);
	void initEntit(std::string fileName, Texture* t,CSource* source);
	virtual ~iwmoEntity();
	void draw(RenderWindow*);
	float GetX();
	float GetY();
	Vector2f GetPos();
	AnimationManager anim;
	virtual void MGetEvent(Event);
	virtual void control();
	virtual void UpdateState();
	AnimationManager* GetTextureAnimation();
	iwmoEntity* MGetBase();
	float SpeedX = 50.0;
	float SpeedY = 70.0;
	EntityState state = unknown;
	void updatetime(float time);
	virtual void deleteentity();
	virtual void tick(float time);
	float time=0.0;
	CSource* m_souc;
	bool visible = true;
	//For kid
	bool ScreenCamera = true;
	bool yourkid = false;
	virtual void shoot(Texture* bullettexture, Vector2i pos);
private:
	float x = 0;
	float y = 0;
};

