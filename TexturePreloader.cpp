#include "TexturePreloader.h"



TexturePreloader::TexturePreloader()
{
}
void TexturePreloader::Preload()
{
	kidSheet = new Texture();
	kidDeathSheet = new Texture();
	if (!kidSheet->loadFromFile("resources/kid.png"))
	{
		cout << "Kid spritesheet not loaded!" << endl;
	}
	if (!kidDeathSheet->loadFromFile("resources/effects/poof.png"))
	{
		cout << "Poof spritesheet not loaded!" << endl;
	}

}

TexturePreloader::~TexturePreloader()
{
}
