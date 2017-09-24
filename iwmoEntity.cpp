#include "iwmoEntity.h"


iwmoEntity::iwmoEntity()
	{

	}
	void iwmoEntity::setPos(Vector2f pos)
	{

		x = pos.x;
		y = pos.y;
	}
	 iwmoEntity* iwmoEntity::MGetBase()
	{
		return ((iwmoEntity*)this);
	}
	void iwmoEntity::initEntit(std::string fileName, sf::Texture* t)
	{
		anim.loadFromXML(fileName, t);
		

	}
	 void iwmoEntity::SettingHandler(GameHandler* h)
	{
		eng->initEntEng(h, MGetBase());
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
		x += xm;
		y += ym;
	}
	iwmoEntity::~iwmoEntity()
	{
		//cout << "entity destructor" << endl;
	}
	int iwmoEntity::GetX()
	{
		return x;
	}
	int iwmoEntity::GetY()
	{
		return y;
	}
	void iwmoEntity::draw(RenderWindow* win)
	{
		//cout << 1;
		anim.draw(win, x, y);
	}
