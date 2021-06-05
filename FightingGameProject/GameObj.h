#pragma once
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "StateController.h"
#include "ScreenVector.h"
#include "DevSettings.h"
#include "JumpSpecs.h"

namespace RB
{
	class GameObj
	{
	public:
		ObjData objData;
		StateController* stateController = nullptr;

		GameObj();
		~GameObj();

		void SetState(State* newState);
		bool SetNextState(State* ptrState);
		void RenderPosition(Camera& cam);
		void RenderSpriteSize(Camera& cam);
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam);
		void AddJump(JumpSpecs jumpSpecs);

		olc::vi2d GetBodyWorldPos(BodyType bodyType);
		std::array<olc::vi2d, 4> GetBodyWorldQuad(BodyType bodyType);
		olc::vi2d GetBoxColliderWorldPos();
		std::array<olc::vi2d, 4> GetBoxColliderWorldQuad();
	};
}