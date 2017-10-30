#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <vector>
using namespace std;
using namespace sf;
namespace Iwmo
{
	class Debug
	{
	public:
		bool Enabled = false;
		vector<RectangleShape> objects;
		void AddRectangle(float x, float y, float w, float h, Color color);
		void AddRectangle(FloatRect rect, Color color);
		void DebugDraw(RenderWindow* target);
	};
}