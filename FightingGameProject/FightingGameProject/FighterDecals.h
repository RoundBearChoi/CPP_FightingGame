#pragma once
#include <vector>
#include "DevSettings.h"
#include "olcPixelGameEngine.h"
#include "DecalLoader.h"
#include "FighterSpriteType.h"
#include "FighterDecalPath.h"

namespace RB
{
	class FighterDecals : public DecalLoader
	{
	public:
		void LoadSprites() override
		{
			IF_COUT{ std::cout << std::endl; }

			for (int32_t i = 0; i < (int32_t)FighterSpriteType::COUNT; i++)
			{
				std::string path = FighterDecalPath::GetPath(i);

				IF_COUT{ std::cout << "constructing Sprite: " << path << std::endl; }

				vecSpritePtr.push_back(new olc::Sprite(path));
			}
		}

		void LoadDecals() override
		{
			for (int i = 0; i < vecSpritePtr.size(); i++)
			{
				IF_COUT{ std::cout << "constructing Decal: " << i << std::endl; }

				vecDecalPtr.push_back(new olc::Decal(vecSpritePtr[i]));
			}
		}

		olc::Decal* GetDecal(int32_t _index) override
		{
			return vecDecalPtr[_index];
		}

		size_t GetSpriteCount() override
		{
			return vecSpritePtr.size();
		}
	};
}