#pragma once
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "CollisionStay.h"
#include "Camera.h"
#include "BodyType.h"

namespace RB
{
	class ObjBase
	{
	public:
		ObjData objData;
		CollisionStay* collisionStay = nullptr;

		virtual void RenderPosition(Camera& cam) = 0;
		virtual void RenderSpriteSize(Camera& cam) = 0;
		virtual void RenderCollisionTiming(BodyType _bodyType, Camera& cam) = 0;

		virtual olc::vi2d GetBodyWorldPos(BodyType bodyType) = 0;
		virtual std::array<olc::vi2d, 4> GetBodyWorldQuad(BodyType bodyType) = 0;

		virtual olc::vi2d GetBoxColliderWorldPos() = 0;
		virtual std::array<olc::vi2d, 4> GetBoxColliderWorldQuad() = 0;
	};
}