#pragma once
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "CollisionData.h"
#include "CollisionStay.h"

namespace RB
{
	class State;
	class StateController;
	class Camera;
	enum class BodyType;

	class ObjBase
	{
	public:
		ObjData objData;
		CollisionData collisionData{ &objData };
		CollisionStay* collisionStay = nullptr;

		virtual State* GetCurrentState() = 0;
		virtual void SetCurrentState(State* state) = 0;
		virtual bool SetNextState(State* ptrState) = 0;
		virtual StateController* GetStateController() = 0;

		virtual void RenderPosition(Camera& cam) = 0;
		virtual void RenderSpriteSize(Camera& cam) = 0;
		virtual void RenderCollisionTiming(BodyType _bodyType, Camera& cam) = 0;

		virtual olc::vi2d GetBodyWorldPos(BodyType bodyType) = 0;
		virtual std::array<olc::vi2d, 4> GetBodyWorldQuad(BodyType bodyType) = 0;

		virtual olc::vi2d GetBoxColliderWorldPos() = 0;
		virtual std::array<olc::vi2d, 4> GetBoxColliderWorldQuad() = 0;
	};
}