#pragma once
#include <iostream>
#include "FighterSpriteType.h"

namespace RB
{
	class FighterDecalPath
	{
	public:
		static std::string GetPath(int32_t _index)
		{
			FighterSpriteType spriteType = (FighterSpriteType)_index;

			switch (spriteType)
			{
			case FighterSpriteType::fighter_0_idle: return "PNG files/fighter_0_idle.png";
			case FighterSpriteType::fighter_1_idle: return "PNG files/fighter_1_idle.png";
			}

			return "none";
		}
	};
}