#pragma once
#include <vector>
#include <iostream>
#include "olcPixelGameEngine.h"
#include "DevSettings.h"

#ifdef _WIN32

#ifdef DEBUG_MODE
#include <experimental/filesystem>
#define FILESYSTEM std::experimental::filesystem
#else
#include <filesystem>
#define FILESYSTEM std::filesystem
#endif

#else
#include <filesystem>
#define FILESYSTEM std::filesystem
#endif

namespace RB
{
	class ExperimentalLoader
	{
	private:
		std::vector<olc::Sprite*> backgroundSprites;
		std::vector<olc::Decal*> backgroundDecals;
		std::vector<size_t> backgroundHash;

		void LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash);

	public:
		static ExperimentalLoader* ptr;

		ExperimentalLoader();
		~ExperimentalLoader();

		void LoadBackgroundSprites();
		void DeleteDecals(std::vector<olc::Sprite*>& spriteVec, std::vector<olc::Decal*>& decalVec);
		olc::Decal* GetBackgroundDecal(size_t _hash);
	};
}