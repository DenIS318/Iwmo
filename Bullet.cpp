#include "Bullet.h"


void Bullet::move()
{
	
	finisheddistance += bulletspeed;
	bulletpos += Vector2i(bulletspeed, 0);
	Iwmo::coutVector2(bulletpos);
}
void Bullet::tick(RenderWindow* win,float time)
{
	move();
	anim.tick(time);
	anim.draw(win,bulletpos.x,bulletpos.y);
}
void Bullet::deletebullet()
{
	delete this;
}
Bullet::Bullet(Vector2i mscale, const Texture* bullettextute,Vector2i pos, string bulletxml)
{
	scale = mscale;
	anim.loadFromXML(bulletxml, (Texture*)(bullettextute));
	anim.animList["shoot"].loop = true;
	anim.play("shoot");
	anim.getSprite()->setScale(scale.x,scale.y);
	bulletpos = pos;
}
Bullet::Bullet(Vector2i mscale, Texture* bullettextute, Vector2i pos, string bulletxml)
{
	scale = mscale;
	anim.loadFromXML(bulletxml, bullettextute);
	anim.animList["shoot"].loop = true;
	anim.play("shoot");
	anim.getSprite()->setScale(scale.x, scale.y);
	bulletpos = pos;
}


Bullet::~Bullet()
{
}
