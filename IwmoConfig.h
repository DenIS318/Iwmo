#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IwmoMath.h"

//CONFIG
namespace Iwmo {
	extern int Width;
	extern int Height;
	extern std::string WindowName;
	extern short framerate;
	extern std::string res;
	extern std::string but;
	extern bool debug;
	extern unsigned short port;
	extern int GRAVITY;
	const sf::Vector2f KidSpawn(100, 3100);
	extern Math IWMOMATH;
	template< typename T >
	void coutVector2(Vector2<T> vector)
	{
		cout << vector.x << ", " << vector.y << endl;
	}
}