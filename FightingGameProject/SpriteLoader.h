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
		std::array<std::vector<olc::Sprite*>, 4> sprites;
		std::array<std::vector<olc::Decal*>, 4> decals;
		std::array<std::vector<size_t>, 4> hashes;

		void LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash);
		
	public:
		static SpriteLoader* ptr;

		SpriteLoader();
		~SpriteLoader();

		void Load_Fighter_0_Sprites();
		void Load_Fighter_1_Sprites();
		void LoadBackgroundSprites();
		void LoadBoxColliderEditorSprites();
		void DeleteSprites(size_t arrayIndex);
		olc::Decal* FindDecal(size_t _hash, size_t arrayIndex);
	};
}