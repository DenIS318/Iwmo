#pragma once
#include "Game.h"

	class MyEntityEngine
	{
	public:
		MyEntityEngine();
		~MyEntityEngine();
		virtual void initEntEng(GameHandler* handlerr, iwmoEntity* ent);
		virtual void MPassEvent(Event);
		inline MyEntityEngine* GetThis();

	private:
		GameHandler* m_handler;
		iwmoEntity* m__entity;
	};
	///////////////////
	class MyKidEngine : public MyEntityEngine
	{
	public:
		MyKidEngine();
		~MyKidEngine();
	};

