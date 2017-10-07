#include "iwmoEntity.h"


iwmoEntity::iwmoEntity()
{

}
void iwmoEntity::control()
{
	
}
void iwmoEntity::setPos(Vector2f pos)
{

	x = pos.x;
	y = pos.y;
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


}//TODO 1
/*void iwmoEntity::SettingHandler(GameHandler* h)
{
	eng->initEntEng(h, MGetBase());
}*/
AnimationManager* iwmoEntity::GetTextureAnimation()
{
	return &anim;
}
void iwmoEntity::MGetEvent(Event event)
{
	
	//cout << "fukyou";
}
void iwmoEntity::m_move(float xm, float ym)
{
	//cout << time << endl;
	x += (xm*30)/1000;
	y += (ym*30)/1000;
	this->setPos(Vector2f(x, y));
}
iwmoEntity::~iwmoEntity()
{
	//cout << "entity destructor" << endl;
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
	//cout << 1;
	anim.draw(win, x, y);
}