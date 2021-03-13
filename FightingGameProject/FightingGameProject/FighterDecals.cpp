#include "FighterDecals.h"

namespace RB
{
	std::string FighterDecals::GetPath(int32_t _spriteTypeIndex)
	{
		FighterSpriteType spriteType = (FighterSpriteType)_spriteTypeIndex;

		switch (spriteType)
		{
		case FighterSpriteType::fighter_0_idle: return "PNG files/fighter_0_idle.png";
		case FighterSpriteType::fighter_1_idle: return "PNG files/fighter_1_idle.png";
		case FighterSpriteType::background_trees_20: return "PNG files/background_trees_20.png";
		case FighterSpriteType::background_mountains: return "PNG files/background_mountains.png";
		case FighterSpriteType::background_sun: return "PNG files/background_sun.png";
		}

		return "none";
	}

	void FighterDecals::LoadSprites()
	{
		IF_COUT{ std::cout << std::endl; }

		for (int32_t i = 0; i < (int32_t)FighterSpriteType::COUNT; i++)
		{
			std::string path = GetPath(i);

			IF_COUT{ std::cout << "constructing Sprite: " << path << std::endl; }

			vecSpritePtr.push_back(new olc::Sprite(path));
		}
	}

	void FighterDecals::LoadDecals()
	{
		for (int32_t i = 0; i < vecSpritePtr.size(); i++)
		{
			IF_COUT{ std::cout << "constructing Decal: " << i << std::endl; }

			vecDecalPtr.push_back(new olc::Decal(vecSpritePtr[i]));
		}
	}

	olc::Decal* FighterDecals::GetDecal(int32_t _index)
	{
		return vecDecalPtr[_index];
	}

	size_t FighterDecals::GetSpriteCount()
	{
		return vecSpritePtr.size();
	}
}