#pragma once
#include <string>
#include <map>
namespace Iwmo {
	enum BlockType
	{
		solid,
		decoration,
		slidable,
		unknownblock
	};
	struct BlockTypes {
		BlockType type;
		const char* name;
	};
}