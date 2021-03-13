#pragma once
#include <vector>
#include "DevSettings.h"
#include "olcPixelGameEngine.h"
#include "DecalLoader.h"
#include "FighterSpriteType.h"

namespace RB
{
	class FighterDecals : public DecalLoader
	{
	public:
		std::string GetPath(int32_t _spriteTypeIndex) override;
		olc::Decal* GetDecal(int32_t _index) override;
		size_t GetSpriteCount() override;

		void LoadSprites() override;
		void LoadDecals() override;
	};
}