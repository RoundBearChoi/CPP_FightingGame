#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;
	class Fighter_0_Jump_Fall;
	class Fighter_0_Jump_WeakPunch;

	class Fighter_0_Jump_Up_Vertical : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_Up_Vertical()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_up_vertical.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_jump_up_vertical.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 1200, 200, 3, 1, 3);
			animationController.status.nTransitionDelay = 6;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter() override
		{
			_objData->SetSpriteSize({ 400, 230 });

			_objData->CreateJumpProcessor();
			_objData->ptrJumpProcessor->SetUpForce(15);
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(_objData->GetPlayerType());

			if (_objData->GetPosition().y >= 0 && stateUpdateCount != 0)
			{
				nextState = State::NewState<Fighter_0_Idle>(_objData);
			}

			else if (_objData->ptrJumpProcessor != nullptr)
			{
				if (_objData->ptrJumpProcessor->GetUpForce() <= 0)
				{
					nextState = State::NewState<Fighter_0_Jump_Fall>(_objData);
				}
			}

			else if (p.weakpunch)
			{
				nextState = State::NewState<Fighter_0_Jump_WeakPunch>(_objData);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}