#pragma once
#include "GameHandler.h"
class MyEntityEngine
{
public:
	MyEntityEngine();
	~MyEntityEngine();
	void initEntEng(GameHandler* handlerr, iwmoEntity* ent);
	void MPassEvent(Event);
	MyEntityEngine* GetThis();
	GameHandler* m_handler;
	iwmoEntity* m__entity;
	const int SpeedX = 1;
	const int SpeedY = 1;
private:


};