#pragma once
#include <vector>
#include "DevSettings.h"
#include "olcPixelGameEngine.h"

namespace RB
{
	class DecalLoader
	{
	protected:
		std::vector<olc::Sprite*> vecSpritePtr;
		std::vector<olc::Decal*> vecDecalPtr;

	public:
		~DecalLoader()
		{
			IF_COUT{ std::cout << "destructing DecalLoader" << std::endl; }

			for (int i = 0; i < vecSpritePtr.size(); i++)
			{
				IF_COUT{ std::cout << "destructing Sprite: " << i << std::endl; }
					
				delete vecSpritePtr[i];
			}

			for (int i = 0; i < vecDecalPtr.size(); i++)
			{
				IF_COUT{ std::cout << "destructing Decal: " << i << std::endl; }
				
				delete vecDecalPtr[i];
			}
		}

		virtual void LoadSprites() = 0;
		virtual void LoadDecals() = 0;
		virtual olc::Decal* GetDecal(int32_t _index) = 0;
		virtual int32_t GetSpriteCount() = 0;
	};
}