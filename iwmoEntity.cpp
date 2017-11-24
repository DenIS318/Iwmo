#include "iwmoEntity.h"

class kid;

iwmoEntity::iwmoEntity()
{

}
bool iwmoEntity::instanceofKid()
{
	return reinterpret_cast<kid*>(this) != NULL;
}
void iwmoEntity::control()
{
	
}
void iwmoEntity::UpdateState()
{

}
void iwmoEntity::deleteentity()
{
	delete this;
}
void iwmoEntity::setPos(Vector2f pos,bool sendpacket)
{

	x = int(pos.x);
	y = int(pos.y);
	if (sendpacket)
	{
		if (yourkid)
		{
			if (mynetwork != NULL)
			{
				KidChangePositionEvent e;
				e.eventtype = Types::EventTypes::KidChangePositionEvent;
				e.whichKid = reinterpret_cast<kid*>(this);
				__raise m_souc->OnCustomEvent(&e);
			}
		}
	}
}
void iwmoEntity::shoot(Texture* bullettexture,Vector2i pos)
{
	auto vec = Vector2i(1, 1);
	Bullet b(vec,bullettexture,pos);
	EntityShootEvent e;
	e.eventtype = Types::EventTypes::EntityShootEvent;
	e.whichEntity = this;
	//TODO
	e.whichBullet = &b;//пуля локальная! измени это потом!
	__raise m_souc->OnCustomEvent(&e);
}
void iwmoEntity::flip(bool b)
{
	anim.flip(b);
	if (yourkid)
	{
		PlayerFlipEvent e;
		e.eventtype = Types::EventTypes::PlayerFlipEvent;
		e.whichEntity = this;
		e.flip = b;
		__raise m_souc->OnCustomEvent(&e);
	}
}
Vector2f iwmoEntity::GetPos()
{
	return Vector2f(x, y);
}
void iwmoEntity::updatetime(float t)
{
	time = t;
}
void iwmoEntity::tick(float t) {

}
iwmoEntity* iwmoEntity::MGetBase()
{
	return ((iwmoEntity*)this);
}
void iwmoEntity::initEntit(std::string fileName, sf::Texture* t, CSource* source)
{
	anim.loadFromXML(fileName, t);
	m_souc = source;
}
AnimationManager* iwmoEntity::GetTextureAnimation()
{
	return &anim;
}
void iwmoEntity::MGetEvent(Event event)
{
}
void iwmoEntity::m_move(int xm, int ym)
{
	int Yoff = (ym * 30) / 1000;
	x += (int)(xm*30)/1000;
	y += Yoff;
	Vector2f newpos(x, y);
	this->setPos(newpos);
	EntityMoveEvent e;
	e.eventtype = Types::EventTypes::EntityMoveEvent;
	e.whichEntity = this;
	__raise m_souc->OnCustomEvent(&e);
	if (yourkid)
	{
		if (mynetwork != NULL)
		{
			KidChangePositionEvent e;
			e.eventtype = Types::EventTypes::KidChangePositionEvent;
			e.whichKid = reinterpret_cast<kid*>(this);
			__raise m_souc->OnCustomEvent(&e);
		}
	}
}
iwmoEntity::~iwmoEntity()
{
	
}
float iwmoEntity::GetX()
{
	return x;
}

float iwmoEntity::GetY()
{
	return y;
}
void iwmoEntity::draw(RenderWindow* win)
{
	
	anim.draw(win, x, y);
}