#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
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
	const sf::Vector2f KidSpawn(50, 3100);
	extern sf::Texture* kidDeathSheet;
}