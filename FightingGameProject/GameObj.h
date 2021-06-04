#pragma once
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "StateController.h"
#include "ScreenVector.h"
#include "DevSettings.h"

namespace RB
{
	class GameObj
	{
	public:
		ObjData objData;
		StateController* stateController = nullptr;

		GameObj();
		~GameObj();

		bool SetNextState(State* ptrState);
		void RenderPosition(Camera& cam);
		void RenderSpriteSize(Camera& cam);
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam);
		void AddJump(int32_t upForce, int32_t sideForce);

		olc::vi2d GetBodyWorldPos(BodyType bodyType);
		std::array<olc::vi2d, 4> GetBodyWorldQuad(BodyType bodyType);
		olc::vi2d GetBoxColliderWorldPos();
	};
}