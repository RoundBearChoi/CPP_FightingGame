#include "ExperimentalLoader.h"

namespace RB
{
	ExperimentalLoader* ExperimentalLoader::ptr;

	ExperimentalLoader::ExperimentalLoader()
	{

	}

	ExperimentalLoader::~ExperimentalLoader()
	{
		for (size_t i = 0; i < sprites.size(); i++)
		{
			DeleteDecals(i);
		}
	}

	void ExperimentalLoader::LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash)
	{
		//load sprites
		for (const auto& i : std::filesystem::directory_iterator(path))
		{
			std::filesystem::path path = i.path();

			IF_COUT{ std::cout << "Loading sprite: " << path << std::endl; };

			std::string p = path.string();
			std::replace(p.begin(), p.end(), '\\', '/'); //convert directory separators
			vecSprites.push_back(new olc::Sprite(p));

			size_t hash = std::hash<std::string>{}(p);
			vecHash.push_back(hash);
		}

		//load decals
		for (size_t i = 0; i < vecSprites.size(); i++)
		{
			IF_COUT{ std::cout << "Loading decal: " << i << std::endl; };

			vecDecals.push_back(new olc::Decal(vecSprites[i]));
		}
	}

	void ExperimentalLoader::LoadBackgroundSprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::BACKGROUND;

		std::string path = "PNG files/Background";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void ExperimentalLoader::DeleteDecals(size_t arrayIndex)
	{
		if (sprites.size() > arrayIndex)
		{
			for (size_t i = 0; i < sprites[arrayIndex].size(); i++)
			{
				if (hashes[arrayIndex].size() > i)
				{
					IF_COUT{ std::cout << "deleting sprite: " << hashes[arrayIndex][i] << std::endl; };
				}

				delete sprites[arrayIndex][i];
			}
		}

		if (decals.size() > arrayIndex)
		{
			for (size_t i = 0; i < decals[arrayIndex].size(); i++)
			{
				if (hashes[arrayIndex].size() > i)
				{
					IF_COUT{ std::cout << "deleting decal: " << hashes[arrayIndex][i] << std::endl; };
				}

				delete decals[arrayIndex][i];
			}
		}
	}

	olc::Decal* ExperimentalLoader::FindDecal(size_t _hash, size_t arrayIndex)
	{
		for (size_t i = 0; i < hashes[arrayIndex].size(); i++)
		{
			if (_hash == hashes[arrayIndex][i])
			{
				if (decals.size() > arrayIndex)
				{
					return decals[arrayIndex][i];
				}
			}
		}

		IF_COUT{ std::cout << "hash not found" << std::endl; }

		return nullptr;
	}
}