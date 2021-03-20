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
		std::vector<olc::Sprite*> backgroundSprites;
		std::vector<olc::Decal*> backgroundDecals;
		std::vector<size_t> backgroundHash;

		void LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash);
		olc::Decal* GetBackgroundDecal(size_t _hash);

	public:
		static ExperimentalLoader* ptr;

		ExperimentalLoader();
		~ExperimentalLoader();

		void LoadBackgroundSprites();
		void DeleteDecals(std::vector<olc::Sprite*>& spriteVec, std::vector<olc::Decal*>& decalVec);
		olc::Decal* GetDecal(SpriteType _spriteType, size_t _hash);
	};
}