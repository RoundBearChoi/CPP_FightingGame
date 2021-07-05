#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Hadouken_Recover : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Hadouken_Recover()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_hadouken_recover.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_hadouken_recover.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 4;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter() override
		{
			_objData->SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			int32_t tiles = animationController.GetTotalTiles() - (int32_t)1;
			size_t end = (size_t)tiles * (size_t)animationController.status.nTransitionDelay;

			if (stateUpdateCount >= end)
			{
				nextState = State::NewState<Fighter_0_Idle>(_objData, _ownerObj);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}