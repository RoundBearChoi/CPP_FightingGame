#pragma once
#include "olcPixelGameEngine.h"
#include "GameData.h"
#include "Camera.h"
#include "DecalLoader.h"

namespace RB
{
	class Scene
	{
	public:
		DecalLoader* ptrDecalLoader;
		Camera cam;

		virtual void InitScene() = 0;
		virtual void Update(GameData& gameData) = 0;
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine) = 0;
		virtual void RenderStates(olc::PixelGameEngine* ptrEngine, bool update) = 0;

		virtual ~Scene();

		void RenderCenterMark(olc::PixelGameEngine* ptrEngine, Camera& cam);
	};
}