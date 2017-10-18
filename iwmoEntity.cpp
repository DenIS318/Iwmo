#include "iwmoEntity.h"



iwmoEntity::iwmoEntity()
{

}
void iwmoEntity::control()
{
	
}
void iwmoEntity::deleteentity()
{
	delete this;
}
void iwmoEntity::setPos(Vector2f pos)
{

	x = int(pos.x);
	y = int(pos.y);
}
void iwmoEntity::shoot(Texture* bullettexture,Vector2i pos)
{
	auto vec = Vector2i(1, 1);
	Bullet b(vec,bullettexture,pos);
	EntityShootEvent e;
	e.eventtype = Types::EventTypes::EntityShootEvent;
	e.whichEntity = this;
	e.whichBullet = &b;//пуля локальная! измени это потом!
	__raise m_souc->OnCustomEvent(e);
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
}
void iwmoEntity::m_moveValid(int xm, int ym,Block* b)
{
	int Yoff = (ym * 30) / 1000;
	x += (int)(xm * 30) / 1000;
	
	IWMOMATH.ValidateDownPos(y, &Yoff, b->GetGlobalRect().top);
	y += Yoff;
	Vector2f newpos(x, y);
	this->setPos(newpos);
	EntityMoveEvent e;
	e.eventtype = Types::EventTypes::EntityMoveEvent;
	e.whichEntity = this;
	__raise m_souc->OnCustomEvent(e);
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
	__raise m_souc->OnCustomEvent(e);
}
iwmoEntity::~iwmoEntity()
{
}
float iwmoEntity::GetX()
{
	return x;
}
void iwmoEntity::GetEventSource(CSource* source)
{
	m_souc = source;
}
float iwmoEntity::GetY()
{
	return y;
}
void iwmoEntity::draw(RenderWindow* win)
{
	anim.draw(win, x, y);
}