#pragma once
#include <iostream>
#include "FighterSpriteType.h"
#include "DecalPath.h"

namespace RB
{
	class FigherDecalPath : public DecalPath
	{
	public:
		int GetCount() override
		{
			return (int)FighterSpriteType::COUNT;
		}

		std::string GetPath(int _index) override
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