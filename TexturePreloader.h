#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
using namespace std;
using namespace sf;
namespace Textures {
	static sf::Texture* kidDeathSheet;
	static sf::Texture* kidSheet;
}
using namespace Textures;
class TexturePreloader
{
public:
	static void Preload();
	
private:
	TexturePreloader();
	~TexturePreloader();
};

