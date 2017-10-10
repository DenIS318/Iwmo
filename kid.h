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

using namespace Iwmo::Events;
class kid : public iwmoEntity
{
public:
	kid();
	/*
	Creates a kid with given XML document filename, texture, position, engine and GameHandler*.
	*/
	void createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine,CSource* eventsource);
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
	int JumpPower = -230;
	bool Alive = true;
	void death();
	bool JumpPassed = false;
	//bool IsMove = false;

private:
	//Vector2f LastPos;
	int lshiftcounter = 0;
	void ProcessKeyboard(Event event);
	//bool animchanged=false;
	void Col();
	void CheckState();
	bool m_p = false;
	iwmoEntity* kidentity = iwmoEntity::MGetBase();

};