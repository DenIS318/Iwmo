#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "tinyxml\tinyxml.h"
#include "IwmoMath.h"
namespace Iwmo {
	int Width = 800;
	int Height = 608;
	std::string WindowName = "I wanna maker online";
	short framerate = 60;
	std::string res = "resources\\";
	std::string but = "button_";
	bool debug = true;
	unsigned short port = 25565;
	int GRAVITY = 10;
	Math IWMOMATH;
}