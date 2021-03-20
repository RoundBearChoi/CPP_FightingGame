#pragma once
#include <vector>
#include <iostream>
#include "olcPixelGameEngine.h"

#ifdef _WIN32
//filesystem not included in VS (strange..)
#include <experimental/filesystem>
#define FILESYSTEM std::experimental::filesystem
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

	public:
		~ExperimentalLoader()
		{
			DeleteDecals(backgroundSprites, backgroundDecals);
		}

		void LoadBackgroundSprites()
		{
			std::string path = "PNG files/Background";
			for (const auto& i : FILESYSTEM::directory_iterator(path))
			{
				FILESYSTEM::path path = i.path();

				std::cout << "Loading: " << path << std::endl;
			}
		}

		void DeleteDecals(std::vector<olc::Sprite*>& spriteVec, std::vector<olc::Decal*>& decalVec)
		{
			for (size_t i = 0; i < spriteVec.size(); i++)
			{
				delete spriteVec[i];
			}

			for (size_t i = 0; i < decalVec.size(); i++)
			{
				delete decalVec[i];
			}
		}
	};
}