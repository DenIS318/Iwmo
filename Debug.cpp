#include "Debug.h"
namespace Iwmo {


	void Debug::AddRectangle(float x, float y, float w, float h, Color color)
	{
		if (!Enabled)
		{
			return;
		}

		auto obj = RectangleShape(Vector2f(w, h));
		obj.setPosition(Vector2f(x, y));
		obj.setFillColor(Color::Transparent);
		obj.setOutlineColor(color);
		obj.setOutlineThickness(1);
		objects.push_back(obj);
	}

	void Debug::AddRectangle(FloatRect rect, Color color)
	{
		AddRectangle(rect.left, rect.top, rect.width, rect.height, color);
	}

	void Debug::DebugDraw(RenderWindow* target)
	{
		if (!Enabled) { return; }
		for (auto it = objects.begin(); it != objects.end(); ++it)
		{
			auto obj = *it._Ptr;
			target->draw(obj);
		}
		objects.clear();
	}
}