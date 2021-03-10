#pragma once
#include <vector>
#include "DevSettings.h"
#include "olcPixelGameEngine.h"
#include "DecalPath.h"

namespace RB
{
	class DecalLoader
	{
	private:
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

		template<class T>
		void LoadSprites()
		{
			IF_COUT{ std::cout << std::endl; }

			if (std::is_base_of<DecalPath, T>::value)
			{
				T pathGetter;

				for (int i = 0; i < pathGetter.GetCount(); i++)
				{
					std::string path = pathGetter.GetPath(i);

					IF_COUT{ std::cout << "constructing Sprite: " << path << std::endl; }

					vecSpritePtr.push_back(new olc::Sprite(path));
				}
			}
		}

		void LoadDecals()
		{
			for (int i = 0; i < vecSpritePtr.size(); i++)
			{
				IF_COUT{ std::cout << "constructing Decal: " << i << std::endl; }
				
				vecDecalPtr.push_back(new olc::Decal(vecSpritePtr[i]));
			}
		}

		olc::Decal* GetDecal(int _index)
		{
			return vecDecalPtr[_index];
		}

		int GetSpriteCount()
		{
			return vecSpritePtr.size();
		}
	};
}