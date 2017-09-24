#include "MyEntityEngine.h"




class MyKidEngine : public MyEntityEngine
{
public:
MyKidEngine();
~MyKidEngine();
void initKidEng(GameHandler* handlerr, iwmoEntity* ent);
void MPassEventKid(Event);
};





MyEntityEngine::MyEntityEngine()
{
}

void MyEntityEngine::initEntEng(GameHandler* handlerr, iwmoEntity* ent)
{
m_handler = handlerr;
m__entity = ent;
__hook(&CSource::OnEvent, m_handler->m_ls, &MyEntityEngine::MPassEvent, this);
}
MyEntityEngine* MyEntityEngine::GetThis()
{
return (MyEntityEngine*)this;
}
void MyEntityEngine::MPassEvent(Event evaent) {

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

void MyKidEngine::MPassEventKid(Event evaent)
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
void MyKidEngine::initKidEng(GameHandler* handlerr, iwmoEntity* ent)
{
m_handler = handlerr;
m__entity = ent;
__hook(&CSource::OnEvent, m_handler->m_ls, &MyEntityEngine::MPassEvent, this);
}
