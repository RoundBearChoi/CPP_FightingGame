#pragma once
#include "olcPixelGameEngine.h"
#include "GameData.h"
#include "DevSettings.h"

namespace RB
{
	class Scene
	{
	protected:
		int ID = 0;

	public:
		virtual void InitScene() {};
		virtual void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) {};
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine) {};
		virtual void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) {};

		virtual ~Scene()
		{
			IF_COUT{ std::cout << "destructing Scene: " << ID << std::endl; }
		}
	};
}