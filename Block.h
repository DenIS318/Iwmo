#pragma once
#pragma warning(disable : 4996)
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
		Uint8 GetTransparency();
		Block(string str, string folder,BlockType blocktype);
		[[deprecated("use string constructor, or set blockname after creation")]]
		 Block(Texture* texture,int x,int y,BlockType blocktype);
		 [[deprecated("use string constructor, or set blockname after creation")]]
		 Block(Texture* texture, sf::Vector2<int>  position, BlockType blocktype);
		 [[deprecated("use string constructor, or set blockname after creation")]]
		Block(Texture* texture, sf::Vector2f  position, BlockType blocktype);
		Block Reset();
		void SetPos(sf::Vector2f pos);
		sf::FloatRect GetGlobalRect();
		~Block();
		Sprite sprite;
		void SetTransparency(Uint8 transparency);
		BlockType blocktype = unknownblock;
		bool killable = false;
		bool animated = false;
		bool Resetable = false;
		bool flipped = false;
		bool trap = false;
		bool fake = false;
		bool jumpthru = false;
		string blockname;
	private:
		int transparency = 255;
		void AddToManager(string texturename, string folder);
	};
	
}