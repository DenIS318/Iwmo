#include "Bullet.h"


void Bullet::move()
{
	//DANGER!!!! GREAT MATH!!!!!!!!!!!!!!!!!!!!!!
	float bulletspeedratio = bulletspeed / 1000;
	finisheddistance += bulletspeedratio;
	auto x = cos(sprite.getRotation()*3.14159265 / 180) * bulletspeedratio;
	auto y = sin(sprite.getRotation()*3.14159265 / 180) * bulletspeedratio;
	bulletpos += Vector2f(x, y);
	//Iwmo::coutVector2(bulletpos);
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
	bulletpos = Vector2f(pos);
}
Bullet::Bullet(Vector2i mscale, Texture* bullettextute, Vector2i pos,string bulletxml)
{
	scale = mscale;
	anim.loadFromXML(bulletxml, bullettextute);
	anim.animList["shoot"].loop = true;
	anim.play("shoot");
	anim.getSprite()->setScale(scale.x, scale.y);
	bulletpos = Vector2f(pos);
}


Bullet::~Bullet()
{
}
