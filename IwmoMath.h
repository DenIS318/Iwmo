#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include "Block.h"
/**
* Test if two sprites overlap using Separating Axis Theorem (http://www.dyn4j.org/2010/01/sat/),
* optionally can receive a pointer to a sf::Vector2f to output the MTV (Minimum Translation Vector)
* to correct the first sprite position
* \param sp1 First sprite
* \param sp2 Second sprite
* \param out_mtv Pointer to a sf::Vector2f in wich to receive the MTV
* \return true if overlapping exist, false otherwise
*/

using namespace std;
using namespace sf;
namespace Iwmo {
	void coutFloatRect(FloatRect R);
	class Math
	{
		
	public:
		~Math();
		Math();
		bool onblock(Iwmo::Block* block, FloatRect entityrect);
		bool hasBlockRight(Iwmo::Block* block, FloatRect entityrect);
		bool hasBlockLeft(Iwmo::Block* block, FloatRect entityrect);
		bool InRange(int val, int minimum, int maximum);
		//bool colTest(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f* out_mtv);
		static double distanceBetweenTwoPoints(double x, double y, double a, double b);
		static  bool sat_test(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f *out_mtv);
		static  bool sat_test(FloatRect sprite1rect, FloatRect sprite2rect, sf::Vector2f *out_mtv);
	};

}