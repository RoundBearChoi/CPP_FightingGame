#pragma once
#include "Camera.h"
#include "CollisionQueue.h"
//#include "InputElement.h"

namespace RB
{
	class InputElement;

	class ObjGroup
	{
	public:
		virtual void UpdateStates(GameData& gameData) = 0;
		virtual void RenderObjPosition(Camera& cam) = 0;
		virtual void RenderStates(Camera& cam, bool update) = 0;
		virtual void RenderBoxColliders(Camera& cam) = 0;
				
		virtual size_t GetObjCount() = 0;
		virtual size_t GetObjCreationID(size_t index) = 0;
		virtual olc::vi2d GetObjWorldPos(size_t index) = 0;
		virtual olc::vi2d GetObjBoxColliderWorldPos(size_t index) = 0;
		virtual std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) = 0;

		virtual void RenderComponents() {}
		virtual void DeleteObj(size_t index) {}
		virtual CollisionQueue* GetCollisionQueue(size_t index) { return nullptr; }
		virtual size_t GetOwnerCreationID(size_t index) { return 0; }
	};
}