#pragma once
#include "Engine.h"
#include "Animation.h"
#include <iostream>
#include "MyListener.h"
#include "iwmoEntity.h"
#include "tmx\MapLoader.hpp"
#include "tmx\MapLayer.hpp"
#include "tmx\MapObject.hpp"
#include "Collision.h"
class kid : public iwmoEntity
{
public:
	kid();
	/*
	Creates a kid with given XML document filename, texture, position, engine and GameHandler*.
	*/
	void createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine);
	void control();
	Engine* m_engine;
	bool grounded = false;
	iwmoEntity* GetEntity();
	int jumpcount = 0;
	Sound jumps;
	Sound doublejumps;
	Sound deaths;
	Sound fires;
	void MGetEvent(Event event);
	Vector2f vel;
	const float MAXVEL_Y = 140;
private:
	void Col();
	
	iwmoEntity* kidentity = iwmoEntity::MGetBase();

};