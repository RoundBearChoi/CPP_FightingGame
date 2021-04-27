#include "SpriteLoader.h"

namespace RB
{
	SpriteLoader* SpriteLoader::ptr;

	SpriteLoader::SpriteLoader()
	{

	}

	SpriteLoader::~SpriteLoader()
	{
		for (size_t i = 0; i < sprites.size(); i++)
		{
			DeleteSprites(i);
		}
	}

	void SpriteLoader::LoadSprites(std::string path, std::vector<olc::Sprite*>& vecSprites, std::vector<olc::Decal*>& vecDecals, std::vector<size_t>& vecHash)
	{
		//load sprites
		for (const auto& i : std::filesystem::directory_iterator(path))
		{
			std::filesystem::path path = i.path();

			IF_COUT{ std::cout << "Loading sprite (original path): " << path << std::endl; };

			std::string p = path.string();
			std::replace(p.begin(), p.end(), '\\', '/'); //convert directory separators
			vecSprites.push_back(new olc::Sprite(p));

			size_t hash = std::hash<std::string>{}(p);
			vecHash.push_back(hash);

			IF_COUT{ std::cout << "converted path: " << p << std::endl; };
			IF_COUT{ std::cout << "hash: " << hash << std::endl; };
		}

		//load decals
		for (size_t i = 0; i < vecSprites.size(); i++)
		{
			IF_COUT{ std::cout << "Loading decal: " << i << std::endl; };

			vecDecals.push_back(new olc::Decal(vecSprites[i]));
		}
	}

	void SpriteLoader::Load_Fighter_0_Sprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::FIGHTER_0;

		std::string path = "PNG files/Fighter_0";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::Load_Fighter_1_Sprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::FIGHTER_1;

		std::string path = "PNG files/Fighter_1";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::LoadBoxColliderEditorSprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::BOXCOLLIDER_EDITOR_UI;

		std::string path = "PNG files/BoxColliderEditor";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::LoadDebugElementSprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::DEBUG_ELEMENTS;

		std::string path = "PNG files/DebugElements";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::LoadInputBufferSprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::INPUT_BUFFER;

		std::string path = "PNG files/InputBuffer";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::LoadProjectileSprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::PROJECTILES;

		std::string path = "PNG files/Projectiles";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::LoadImpactEffectSprites()
	{
		int32_t arrayIndex = (int32_t)SpriteType::IMPACT_EFFECTS;

		std::string path = "PNG files/ImpactEffects";
		LoadSprites(path, sprites[arrayIndex], decals[arrayIndex], hashes[arrayIndex]);
	}

	void SpriteLoader::DeleteSprites(size_t arrayIndex)
	{
		if (sprites.size() > arrayIndex)
		{
			for (size_t i = 0; i < sprites[arrayIndex].size(); i++)
			{
				if (hashes[arrayIndex].size() > i)
				{
					IF_COUT{ std::cout << "deleting sprite " << i << ": " << hashes[arrayIndex][i] << std::endl; };
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
					IF_COUT{ std::cout << "deleting decal " << i << ": " << hashes[arrayIndex][i] << std::endl; };
				}

				delete decals[arrayIndex][i];
			}
		}
	}

	olc::Decal* SpriteLoader::FindDecal(size_t _hash, size_t arrayIndex)
	{
		if (hashes.size() > arrayIndex)
		{
			for (size_t i = 0; i < hashes[arrayIndex].size(); i++)
			{
				if (_hash == hashes[arrayIndex][i])
				{
					if (decals.size() > arrayIndex)
					{
						if (decals[arrayIndex].size() > i)
						{
							return decals[arrayIndex][i];
						}
					}
				}
			}
		}

		IF_COUT{ std::cout << "hash not found" << std::endl; }

		return nullptr;
	}
}