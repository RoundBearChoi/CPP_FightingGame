#pragma once
#include "olcPixelGameEngine.h"
#include "GameData.h"
#include "DevSettings.h"

namespace RB
{
	class Scene
	{
	protected:
		//GameObjList objList;
		//DecalLoader* decalLoader;

	public:
		virtual void InitScene() = 0;
		virtual void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) = 0;
		virtual void RenderObjs(olc::PixelGameEngine* ptrEngine) = 0;
		virtual void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) = 0;

		Scene()
		{
			IF_COUT
			{ 
				std::cout << std::endl;
				std::cout << "constructing Scene (virtual)" << std::endl;
			}
		}

		virtual ~Scene()
		{

		}
	};
}