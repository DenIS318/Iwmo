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
	struct BlockSettings {
			int layer;
			string name, folder;
			bool Killable;
			bool Resetable;
			float ScaleX = 1.0f, ScaleY = 1.0f;
			BlockType blocktype = solid;
			bool fake;
			int transparency = 255;
			bool jumpthru;
			
	};
}