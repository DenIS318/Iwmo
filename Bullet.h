#pragma once
#include <SFML\Graphics.hpp>
#include "tinyxml\tinyxml.h"
#include <iostream>
#include "Animation.h"
#include "IwmoConfig.h"
#define Vector2i sf::Vector2i
using namespace std;
using namespace sf;
class Bullet
{
public:
	void move();
	void tick(RenderWindow* wind,float time);
	Bullet(Vector2i scale, Texture* bullettextute, Vector2i pos, string bulletxml = "resources/bullet.xml");
	Bullet(Vector2i scale,const Texture* bullettextute, Vector2i pos, string bulletxml = "resources/bullet.xml");
	~Bullet();
	Vector2i scale;
	Sprite sprite;
	void deletebullet();
	AnimationManager anim;
	int bulletspeed = 2;
	int finisheddistance = 0;
	int maxdistance = 400;
	Vector2i bulletpos;
};
#undef Vector2i

