#include "iwmoEntity.h"


iwmoEntity::iwmoEntity()
{

}
void iwmoEntity::control()
{
	
}
void iwmoEntity::setPos(Vector2f pos)
{

	x = int(pos.x);
	y = int(pos.y);
}
Vector2f iwmoEntity::GetPos()
{
	return Vector2f(x, y);
}
void iwmoEntity::updatetime(float t) {
	time = t;
}
iwmoEntity* iwmoEntity::MGetBase()
{
	return ((iwmoEntity*)this);
}
void iwmoEntity::initEntit(std::string fileName, sf::Texture* t)
{
	
	anim.loadFromXML(fileName, t);
}
AnimationManager* iwmoEntity::GetTextureAnimation()
{
	return &anim;
}
void iwmoEntity::MGetEvent(Event event)
{
	
	//cout << "fukyou";
}
void iwmoEntity::m_move(int xm, int ym)
{
	//cout << time << endl;
	x += (int)(xm*30)/1000;
	y += (int)(ym*30)/1000;
	/*if (xm > 0)
	{
		if (anim.isFlip())
		{
			anim.flip(false);
		}
	}
	else
	{
		if (!anim.isFlip())
		{
			anim.flip(true);
		}
	}*/
	this->setPos(Vector2f(x, y));
	EntityMoveEvent e;
	e.eventtype = Types::EventTypes::EntityMoveEvent;
	e.whichEntity = this;
	__raise m_souc->OnCustomEvent(e);
}
iwmoEntity::~iwmoEntity()
{
	//cout << "entity destructor" << endl;
}
float iwmoEntity::GetX()
{
	return x;
}
void iwmoEntity::GetEventSource(CSource* source)
{
	
	//cout << "Entity hooked!" << endl;
	m_souc = source;
}
float iwmoEntity::GetY()
{
	return y;
}
void iwmoEntity::draw(RenderWindow* win)
{
	//cout << 1;
	anim.draw(win, x, y);
}