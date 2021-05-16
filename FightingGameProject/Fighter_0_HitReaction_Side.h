#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_HitReaction_Side : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_HitReaction_Side()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_hitreaction_side.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_hitreaction_side.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 400, 200, 1, 1, 1);
			animationController.status.nTransitionDelay = 8;
		}

		void OnEnter() override
		{
			_objData->SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			int32_t e0 = animationController.status.nTransitionDelay * (int32_t)1;
			int32_t e1 = animationController.status.nTransitionDelay * (int32_t)2;
			int32_t e2 = animationController.status.nTransitionDelay * (int32_t)3;

			if (updateCount == 0 && updateCount < e0)
			{
				int32_t speed = Directions::GetBackSpeed(_objData->IsFacingRight(), 2);
				olc::vi2d pos = _objData->GetPosition();
				pos.x += speed;
				_objData->SetPosition(pos);
			}
			else if (updateCount < e1)
			{
				int32_t speed = Directions::GetBackSpeed(_objData->IsFacingRight(), 1);
				olc::vi2d pos = _objData->GetPosition();
				pos.x += speed;
				_objData->SetPosition(pos);
			}
			else if (updateCount >= e2)
			{
				nextState = State::NewState<Fighter_0_Idle>(_objData);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}