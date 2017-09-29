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
	//kid();
	//	~kid();

	/*
	Creates a kid with given XML document filename, texture, position, engine and GameHandler*.
	*/
	void createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine);
	//TODO 5
	void MGetEvent(Event event);
	void control();
	Engine* m_engine;
	bool grounded = false;
	bool colUP,
		colDOWN,
		colRIGHT,
		colLEFT;
	//void SetHandler(GameHandler*);
	//iwmoEntity* entity = iwmoEntity::GetBase();
	//DerivedType * m_derivedType = dynamic_cast<DerivedType*>(&m_baseType);
	iwmoEntity* GetEntity();
private:
	iwmoEntity* kidentity = iwmoEntity::MGetBase();

};