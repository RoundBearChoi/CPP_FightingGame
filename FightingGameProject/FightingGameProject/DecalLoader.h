#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "DevSettings.h"

namespace RB
{
	class DecalLoader
	{
	protected:
		std::vector<olc::Sprite*> vecSpritePtr;
		std::vector<olc::Decal*> vecDecalPtr;

	public:
		virtual std::string GetPath(int32_t _spriteTypeIndex) = 0;
		virtual void LoadSprites() = 0;
		virtual void LoadDecals() = 0;
		virtual olc::Decal* GetDecal(int32_t _index) = 0;
		virtual size_t GetSpriteCount() = 0;

		~DecalLoader()
		{
			IF_COUT{ std::cout << "destructing DecalLoader" << std::endl; }

			for (int32_t i = 0; i < vecSpritePtr.size(); i++)
			{
				IF_COUT{ std::cout << "destructing Sprite: " << i << std::endl; }
					
				delete vecSpritePtr[i];
			}

			for (int32_t i = 0; i < vecDecalPtr.size(); i++)
			{
				IF_COUT{ std::cout << "destructing Decal: " << i << std::endl; }
				
				delete vecDecalPtr[i];
			}
		}
	};
}