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
		std::vector<size_t> backgroundHash;

	public:
		~ExperimentalLoader()
		{
			DeleteDecals(backgroundSprites, backgroundDecals);
		}

		void LoadBackgroundSprites()
		{
			std::string path = "PNG files/Background";

			//load sprites
			for (const auto& i : FILESYSTEM::directory_iterator(path))
			{
				FILESYSTEM::path path = i.path();
				
				std::cout << "Loading sprite: " << path << std::endl;

				std::string fileName = path.u8string();
				backgroundSprites.push_back(new olc::Sprite(fileName));

				size_t hash = std::hash<std::string>{}(fileName);
				//size_t testhash = std::hash<std::string>{}("PNG files\\Background\\background_mountains.png");

				std::cout << hash << std::endl;
				//std::cout << testhash << std::endl;

				backgroundHash.push_back(hash);
			}

			//load decals
			for (size_t i = 0; i < backgroundSprites.size(); i++)
			{
				IF_COUT{ std::cout << "Loading decal: " << i << std::endl; }

				backgroundDecals.push_back(new olc::Decal(backgroundSprites[i]));
			}
		}

		void DeleteDecals(std::vector<olc::Sprite*>& spriteVec, std::vector<olc::Decal*>& decalVec)
		{
			for (size_t i = 0; i < spriteVec.size(); i++)
			{
				std::cout << "deleting sprite: " << backgroundHash[i] << std::endl;
				delete spriteVec[i];
			}

			for (size_t i = 0; i < decalVec.size(); i++)
			{
				std::cout << "deleting decal: " << backgroundHash[i] << std::endl;
				delete decalVec[i];
			}
		}
	};
}