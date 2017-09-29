#include "IwmoMath.h"


namespace Iwmo
{
	Math::Math()
	{
	}

	double Math::distanceBetweenTwoPoints(double x, double y, double a, double b) {
		return sqrt(pow(x - a, 2) + pow(y - b, 2));
	}
	Math::~Math()
	{
	}
}