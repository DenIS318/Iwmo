#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>

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
namespace Iwmo {
	class Math
	{
		
	public:
		~Math();
		Math();
		//bool colTest(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f* out_mtv);
		static double distanceBetweenTwoPoints(double x, double y, double a, double b);
		static  bool sat_test(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f *out_mtv);
	};

}