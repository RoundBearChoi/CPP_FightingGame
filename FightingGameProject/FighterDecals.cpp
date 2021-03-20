#include "FighterDecals.h"
#include "FighterSpriteType.h"

namespace RB
{
	std::string FighterDecals::GetPath(int32_t _spriteTypeIndex)
	{
		FighterSpriteType spriteType = (FighterSpriteType)_spriteTypeIndex;

		switch (spriteType)
		{
		case FighterSpriteType::fighter_0_idle: return "PNG files/fighter_0_idle.png";
		case FighterSpriteType::fighter_0_walk: return "PNG files/fighter_0_walk.png";
		case FighterSpriteType::fighter_0_jab: return "PNG files/fighter_0_jab.png";
		case FighterSpriteType::fighter_1_idle: return "PNG files/fighter_1_idle.png";

		case FighterSpriteType::background_trees_20: return "PNG files/background_trees_20.png";
		case FighterSpriteType::background_mountains: return "PNG files/background_mountains.png";
		case FighterSpriteType::background_sun: return "PNG files/background_sun.png";

		case FighterSpriteType::editor_playframe: return "PNG files/editor_playframe.png";
		case FighterSpriteType::editor_save: return "PNG files/editor_save.png";
		case FighterSpriteType::editor_left_sel: return "PNG files/editor_left_sel.png";
		case FighterSpriteType::editor_right_sel: return "PNG files/editor_right_sel.png";
		}

		return "none";
	}

	olc::Decal* FighterDecals::GetDecal(int32_t _index)
	{
		return vecDecalPtr[_index];
	}

	size_t FighterDecals::GetSpriteCount()
	{
		return vecSpritePtr.size();
	}

	void FighterDecals::LoadSprites()
	{
		IF_COUT{ std::cout << std::endl; };

		for (int32_t i = 0; i < (int32_t)FighterSpriteType::COUNT; i++)
		{
			std::string path = GetPath(i);

			IF_COUT{ std::cout << "constructing Sprite: " << path << std::endl; };

			vecSpritePtr.push_back(new olc::Sprite(path));
		}
	}

	void FighterDecals::LoadDecals()
	{
		for (int32_t i = 0; i < vecSpritePtr.size(); i++)
		{
			IF_COUT{ std::cout << "constructing Decal: " << i << std::endl; };

			vecDecalPtr.push_back(new olc::Decal(vecSpritePtr[i]));
		}
	}
}