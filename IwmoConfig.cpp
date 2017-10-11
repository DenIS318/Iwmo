#include <iostream>
#include <SFML\Graphics.hpp>
#include "tinyxml\tinyxml.h"
namespace Iwmo {
	int Width = 800;
	int Height = 600;
	std::string WindowName = "I wanna maker online";
	short framerate = 60;
	std::string res = "resources\\";
	std::string but = "button_";
	bool debug = true;
	unsigned short port = 25565;
	int GRAVITY = 10;
	sf::Texture* kidDeathSheet = new sf::Texture;
	//const sf::Vector2f KidSpawn(50, 3100);
}