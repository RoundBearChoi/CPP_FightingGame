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
		virtual void InitScene() {};
		virtual void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) {};
		virtual void RenderObjs(olc::PixelGameEngine* ptrEngine) {};
		virtual void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) {};

		virtual ~Scene() {}
	};
}