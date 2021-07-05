#pragma once
#include "ObjBase.h"
#include "StateController.h"
#include "Camera.h"
#include "BodyType.h"
#include "ScreenVector.h"
#include "DevSettings.h"

namespace RB
{
	class GameObj : public ObjBase
	{
	private:
		StateController* _stateController = nullptr;

	public:
		GameObj();
		~GameObj();

		State* GetCurrentState() override;
		bool SetNextState(State* ptrState) override;
		void SetCurrentState(State* state) override;

		StateController* GetStateController() override;

		void RenderPosition(Camera& cam) override;
		void RenderSpriteSize(Camera& cam) override;
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam) override;

		olc::vi2d GetBodyWorldPos(BodyType bodyType) override;
		std::array<olc::vi2d, 4> GetBodyWorldQuad(BodyType bodyType) override;

		olc::vi2d GetBoxColliderWorldPos() override;
		std::array<olc::vi2d, 4> GetBoxColliderWorldQuad() override;
	};
}