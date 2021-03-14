#pragma once
#include "olcPixelGameEngine.h"
#include "Camera.h"
#include "DecalLoader.h"

namespace RB
{
	class ObjGroup
	{
	public:
		virtual void UpdateState(GameData& gameData) = 0;
		virtual void RenderObjPosition(Camera& cam) = 0;
		virtual void RenderStates(DecalLoader* ptrDecalLoader, Camera& cam, bool update) = 0;
	};
}
