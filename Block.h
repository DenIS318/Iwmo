#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
using namespace sf;
using namespace std;
namespace Iwmo {
	class Block
	{
	public:
		enum BlockType
		{
			solid,
			decoration,
			killing,
			trap
		};
		Block(string str);
		Block(Texture* texture,int x,int y);
		Block(Texture* texture, sf::Vector2<int>  position);
		Block(Texture* texture, sf::Vector2f  position);
		Block Reset();
		void SetPos(sf::Vector2f pos);
		sf::FloatRect GetGlobalRect();
		~Block();
		Sprite sprite;
		BlockType blocktype = solid;
		bool Resetable = false;
	private:
		void AddToManager(string texturename);
	};
	
}