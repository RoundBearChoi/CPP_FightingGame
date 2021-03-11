#pragma once
#include "olcPixelGameEngine.h"
#include "Camera.h"

namespace RB
{
	class ObjGroup
	{
	public:
		virtual void UpdateState(GameData& gameData) = 0;
		virtual void RenderObjPosition(olc::PixelGameEngine* ptrEngine, Camera& cam) = 0;
		virtual void RenderStates(olc::PixelGameEngine* ptrEngine, DecalLoader* ptrDecalLoader, Camera& cam, bool update) = 0;
	};
}
