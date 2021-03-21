#pragma once
#include <vector>
#include <iostream>
#include <filesystem>
#include "olcPixelGameEngine.h"
#include "DevSettings.h"
#include "SpriteType.h"

namespace RB
{
	class ExperimentalLoader
	{
	private:
		std::array<std::vector<olc::Sprite*>, 2> sprites;
		std::array<std::vector<olc::Decal*>, 2> decals;
		std::array<std::vector<size_t>, 2> hashes;

		void LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash);
		
	public:
		static ExperimentalLoader* ptr;

		ExperimentalLoader();
		~ExperimentalLoader();

		void Load_Fighter_0_Sprites();
		void LoadBackgroundSprites();
		void DeleteDecals(size_t arrayIndex);
		olc::Decal* FindDecal(size_t _hash, size_t arrayIndex);
	};
}