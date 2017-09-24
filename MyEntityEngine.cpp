#include "MyEntityEngine.h"



	const int SpeedX = 1;
	const int SpeedY = 1;

	MyEntityEngine::MyEntityEngine()
	{
	}
	void MyEntityEngine::MPassEvent(Event evaent)
	{
		cout << "Event passed" << endl;
		switch (evaent.type)
		{
		case Event::KeyPressed:
			switch (evaent.key.code)
			{
			case Keyboard::D:
				m__entity->m_move(SpeedX, SpeedY);
				m__entity->anim.flip(false);
				break;
			case Keyboard::A:
				m__entity->m_move(-SpeedX, -SpeedY);
				m__entity->anim.flip(true);
				break;
			}
			break;
		}
	}
	void MyEntityEngine::initEntEng(GameHandler* handlerr, iwmoEntity* ent)
	{
		m_handler = handlerr;
		m__entity = ent;
		__hook(&CSource::OnEvent, m_handler->m_ls, &MyEntityEngine::MPassEvent, this);
	}
	inline MyEntityEngine* MyEntityEngine::GetThis()
	{
		return (MyEntityEngine*)this;
	}

	MyEntityEngine::~MyEntityEngine()
	{
	}
	/////////////////////////
	MyKidEngine::MyKidEngine()
	{
	}


	MyKidEngine::~MyKidEngine()
	{
	}
