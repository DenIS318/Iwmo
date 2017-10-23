#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
//#include "IwmoConfig.h"
#include "iwmoTypes.h"
using namespace sf;
using namespace std;
using namespace Iwmo;
namespace Iwmo {
	class Block
	{
	public:
		
		Block(string str, BlockType blocktype);
		Block(Texture* texture,int x,int y,BlockType blocktype);
		Block(Texture* texture, sf::Vector2<int>  position, BlockType blocktype);
		Block(Texture* texture, sf::Vector2f  position, BlockType blocktype);
		Block Reset();
		void SetPos(sf::Vector2f pos);
		sf::FloatRect GetGlobalRect();
		~Block();
		Sprite sprite;
		BlockType blocktype = unknownblock;
		bool killable = false;
		bool animated = false;
		bool Resetable = false;
		bool flipped = false;
		bool trap = false;
	private:
		void AddToManager(string texturename);
	};
	
}