#include "IwmoMath.h"


namespace Iwmo
{
	void Iwmo::coutFloatRect(FloatRect R)
	{
		cout << R.left << " " << R.top << " " << R.width << " " << R.height << endl;
	}
	Iwmo::Math::Math()
	{
	}
	bool Iwmo::Math::InRange(int val, int minimum, int maximum)
	{
		return ((minimum <= val) && (val <= maximum));
	}
	double  Iwmo::Math::distanceBetweenTwoPoints(double x, double y, double a, double b) {
		return sqrt(pow(x - a, 2) + pow(y - b, 2));
	}
	Iwmo::Math::~Math()
	{
	}
	bool Iwmo::Math::onblock(Iwmo::Block* b, FloatRect entityrect)
	{
		
		
		FloatRect brect = b->GetGlobalRect();
		auto val = 0.1;
		brect.height = brect.height + val;
		brect.top = brect.top - val;
		if (brect.intersects(entityrect))
		{
			return true;
		}
		return false;
	}
	bool Iwmo::Math::hasBlockRight(Iwmo::Block* b, FloatRect entityrect)
	{
		FloatRect brect = b->GetGlobalRect();
		brect.left = brect.left - 0.1;
		if (brect.intersects(entityrect))
		{
			return true;
		}
		return false;
	}
	
	bool Iwmo::Math::hasBlockLeft(Iwmo::Block* b, FloatRect entityrect)
	{

		
		FloatRect brect = b->GetGlobalRect();
		brect.width = brect.width + 0.1;
		if (brect.intersects(entityrect))
		{
			return true;
		}
		return false;
	}
	bool Iwmo::Math::sat_test(const FloatRect floatrect1, const FloatRect floatrect2, sf::Vector2f *out_mtv) {
		const sf::FloatRect rectSp1 = floatrect1;
		const sf::FloatRect rectSp2 = floatrect2;
		float proj_x, proj_y, overlap_x, overlap_y;

		// test overlap in x axis
		proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
		if (proj_x < rectSp1.width + rectSp2.width) {
			if (out_mtv) {
				// calculate mtv in x
				overlap_x = rectSp1.width + rectSp2.width - proj_x;
			}
			// test overlap in y axis
			proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
			if (proj_y < rectSp1.height + rectSp2.height) {
				if (out_mtv) {
					// calculate mtv in y
					overlap_y = rectSp1.height + rectSp2.height - proj_y;
					out_mtv->x = out_mtv->y = 0;

					// choose minimun overlap
					if (overlap_x < overlap_y) {
						out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
					}
					else {
						out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
					}
				}
				return true;
			}
		}
		return false;
	}
	bool Iwmo::Math::sat_test(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f *out_mtv) {
		const sf::FloatRect &rectSp1 = sp1.getGlobalBounds();
		const sf::FloatRect &rectSp2 = sp2.getGlobalBounds();
		float proj_x, proj_y, overlap_x, overlap_y;

		// test overlap in x axis
		proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
		if (proj_x < rectSp1.width + rectSp2.width) {
			if (out_mtv) {
				// calculate mtv in x
				overlap_x = rectSp1.width + rectSp2.width - proj_x;
			}
			// test overlap in y axis
			proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
			if (proj_y < rectSp1.height + rectSp2.height) {
				if (out_mtv) {
					// calculate mtv in y
					overlap_y = rectSp1.height + rectSp2.height - proj_y;
					out_mtv->x = out_mtv->y = 0;

					// choose minimun overlap
					if (overlap_x < overlap_y) {
						out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
					}
					else {
						out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
					}
				}
				return true;
			}
		}
		return false;
	}
}
