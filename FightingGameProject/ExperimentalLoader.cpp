#include "ExperimentalLoader.h"

namespace RB
{
	ExperimentalLoader* ExperimentalLoader::ptr;

	ExperimentalLoader::ExperimentalLoader()
	{

	}

	ExperimentalLoader::~ExperimentalLoader()
	{
		DeleteDecals(backgroundSprites, backgroundDecals);
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
		std::string path = "PNG files/Background";
		LoadSprites(path, backgroundSprites, backgroundDecals, backgroundHash);
	}

	void ExperimentalLoader::DeleteDecals(std::vector<olc::Sprite*>& spriteVec, std::vector<olc::Decal*>& decalVec)
	{
		for (size_t i = 0; i < spriteVec.size(); i++)
		{
			IF_COUT{ std::cout << "deleting sprite: " << backgroundHash[i] << std::endl; };
			delete spriteVec[i];
		}

		for (size_t i = 0; i < decalVec.size(); i++)
		{
			IF_COUT{ std::cout << "deleting decal: " << backgroundHash[i] << std::endl; };
			delete decalVec[i];
		}
	}

	olc::Decal* ExperimentalLoader::GetDecal(SpriteType _spriteType, size_t _hash)
	{
		if (_spriteType == SpriteType::BACKGROUND)
		{
			return GetBackgroundDecal(_hash);
		}
	}

	olc::Decal* ExperimentalLoader::GetBackgroundDecal(size_t _hash)
	{
		for (size_t i = 0; i < backgroundHash.size(); i++)
		{
			if (_hash == backgroundHash[i])
			{
				return backgroundDecals[i];
			}
		}

		IF_COUT{ std::cout << "hash not found" << std::endl; }

		return nullptr;
	}
}