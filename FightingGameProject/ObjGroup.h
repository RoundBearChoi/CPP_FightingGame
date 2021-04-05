#pragma once
#include "Camera.h"

namespace RB
{
	class ObjGroup
	{
	public:
		virtual void UpdateStates(GameData& gameData) = 0;
		virtual void RenderObjPosition(Camera& cam) = 0;
		virtual void RenderStates(Camera& cam, bool update) = 0;
		virtual void RenderBoxColliders(Camera& cam) = 0;
		virtual size_t GetObjCount() = 0;
		virtual olc::vi2d GetObjWorldPos(size_t index) = 0;
		virtual olc::vi2d GetObjBoxColliderWorldPos(size_t index) = 0;
	};
}