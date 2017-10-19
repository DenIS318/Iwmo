#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IwmoMath.h"
//CONFIG

namespace Iwmo {
	//defines layers
#define bg2 0
#define bg 1
#define tiles 2
#define tiles2 3
#define bounds 4
#define deathzone 5
#define objects 6
#define textlayer 7
	enum BlockType
	{
		solid,
		decoration,
		trap,
		unknownblock
	};
	extern int Width;
	extern int Height;
	extern std::string WindowName;
	extern short framerate;
	extern std::string res;
	extern std::string but;
	extern bool debug;
	extern unsigned short port;
	extern int GRAVITY;
	const sf::Vector2f KidSpawn(100, 3600-32);
	extern Math IWMOMATH;
	template< typename T >
	void coutVector2(Vector2<T> vector)
	{
		cout << vector.x << ", " << vector.y << endl;
	}
	struct IwmoBlock {
		/*
		Block name without dot
		*/
		string blockname;
		/*
		Pointer to block texture
		*/
		Texture* textureptr;
		/*
		Blocktype, see Block::BlockType
		*/
		BlockType blocktype;
	};
}