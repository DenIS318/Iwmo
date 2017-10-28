#pragma once
#include <vector>
#include "Block.h"
#include <iostream>
#include "iwmoTypes.h"
#include "IwmoConfig.h"
using namespace std;
namespace Iwmo {
	class IwmoLayer {
	public:
		IwmoLayer::IwmoLayer();
		IwmoLayer::~IwmoLayer();
		bool visible = true;
		std::vector<Block*> objects;
	private:
	};
}