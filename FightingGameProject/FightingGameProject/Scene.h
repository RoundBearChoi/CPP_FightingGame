#pragma once
#include "olcPixelGameEngine.h"
#include "GameData.h"
#include "DevSettings.h"
#include "Camera.h"

namespace RB
{
	class Scene
	{
	protected:
		int ID = 0;

	public:
		Camera cam;

		virtual void InitScene() = 0;
		virtual void UpdateScene(olc::PixelGameEngine* ptrEngine, GameData& gameData) = 0;
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine) = 0;
		virtual void RenderStates(bool update, olc::PixelGameEngine* ptrEngine) = 0;

		virtual ~Scene()
		{
			IF_COUT{ std::cout << "destructing Scene (virtual): " << ID << std::endl; }
		}
	};
}