#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IwmoMath.h"
//CONFIG
#include "iwmoTypes.h"
namespace Iwmo {
	//defines layers
#define bg2l 0
#define bgl 1
#define tilesl 2
#define tiles2l 3
#define boundsl 4
#define deathzonel 5
#define objectsl 6
#define textlayerl 7
	
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