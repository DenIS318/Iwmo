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
	bool Iwmo::Math::ValidateDownPos(int entityY,int* Yoffset,int targetTOP)
	{
		
		auto offsetedval = entityY + *Yoffset;
		if (offsetedval > targetTOP)
		{
			*Yoffset = offsetedval-targetTOP;
			cout << "VALIDATED " << endl;
			cout << Yoffset << endl;
			return true;
		}
		return false;
		
	}
	/*bool Iwmo::Math::colTest(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f* out_mtv)
	{
		const sf::FloatRect &rectSp1 = sp1.getGlobalBounds();
		const sf::FloatRect &rectSp2 = sp2.getGlobalBounds();
		const sf::FloatRect &rectSp1Y = sp1.getGlobalBounds();
		const sf::FloatRect &rectSp2Y = sp2.getGlobalBounds();
		float proj_x, proj_y, overlap_x, overlap_y;

		// test overlap in x axis
		proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
		if (proj_x < rectSp1.width + rectSp2.width) {
				// calculate mtv in x
				overlap_x = rectSp1.width + rectSp2.width - proj_x;
		}
		cout << rectSp1Y.height << ", " << rectSp2Y.top << endl;
		if (rectSp1Y.height >= rectSp2Y.top)
		{
			cout << "colided" << endl;
			out_mtv->x = overlap_x;
			out_mtv->y = rectSp2Y.top - rectSp1Y.height;
			return true;
		}
		else
		{
			return false;
		}
	}*/
	bool Iwmo::Math::onblock(Iwmo::Block* b, FloatRect entityrect)
	{
		
		entityrect.top +=  0.1;
		FloatRect brect = b->GetGlobalRect();
		if (brect.intersects(entityrect))
		{
			return true;
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
