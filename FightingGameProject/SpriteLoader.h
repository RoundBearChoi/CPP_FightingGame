#pragma once
#include <vector>
#include <iostream>
#include <filesystem>
#include "olcPixelGameEngine.h"
#include "DevSettings.h"
#include "SpriteType.h"

namespace RB
{
	class SpriteLoader
	{
	private:
		std::array<std::vector<olc::Sprite*>, (int32_t)SpriteType::COUNT> sprites;
		std::array<std::vector<olc::Decal*>, (int32_t)SpriteType::COUNT> decals;
		std::array<std::vector<size_t>, (int32_t)SpriteType::COUNT> hashes;

		void LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash);
		
	public:
		static SpriteLoader* ptr;

		SpriteLoader();
		~SpriteLoader();

		void Load_Fighter_0_Sprites();
		void Load_Fighter_1_Sprites();
		void LoadBoxColliderEditorSprites();
		void LoadDebugElementSprites();
		void LoadInputBufferSprites();
		void LoadProjectileSprites();
		void LoadImpactEffectSprites();
		void DeleteSprites(size_t arrayIndex);
		olc::Decal* FindDecal(size_t _hash, size_t arrayIndex);
	};
}