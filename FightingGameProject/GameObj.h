#pragma once
#include "ObjBase.h"
#include "StateController.h"
#include "ScreenVector.h"
#include "DevSettings.h"

namespace RB
{
	class GameObj : public ObjBase
	{
	public:
		StateController* stateController = nullptr;
		
		GameObj();
		~GameObj();

		void RenderPosition(Camera& cam) override;
		void RenderSpriteSize(Camera& cam) override;
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam) override;

		State* GetCurrentState() override;

		olc::vi2d GetBodyWorldPos(BodyType bodyType) override;
		std::array<olc::vi2d, 4> GetBodyWorldQuad(BodyType bodyType) override;

		olc::vi2d GetBoxColliderWorldPos() override;
		std::array<olc::vi2d, 4> GetBoxColliderWorldQuad() override;

		void SetState(State* newState);
		bool SetNextState(State* ptrState);
	};
}