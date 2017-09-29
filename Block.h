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
		Block(string str);
		Block(Texture* texture,int x,int y);
		Block(Texture* texture, Vector2<int>  position);
		Block(Texture* texture, Vector2f  position);
		void SetPos(Vector2f pos);
		~Block();
		Sprite sprite;
	private:
		void AddToManager(string texturename);
	};
	
}