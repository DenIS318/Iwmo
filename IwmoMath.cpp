#include "IwmoMath.h"


namespace Iwmo
{
	Iwmo::Math::Math()
	{
	}

	double  Iwmo::Math::distanceBetweenTwoPoints(double x, double y, double a, double b) {
		return sqrt(pow(x - a, 2) + pow(y - b, 2));
	}
	Iwmo::Math::~Math()
	{
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