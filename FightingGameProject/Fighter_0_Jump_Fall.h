#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;
	class Fighter_0_Jump_WeakPunch;

	class Fighter_0_Jump_Fall : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_Fall()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_fall.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_jump_fall.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 800, 200, 2, 1, 2);
			animationController.status.nTransitionDelay = 10;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter() override
		{
			_objData->SetSpriteSize({ 420, 220 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(_objData->GetPlayerType());

			if (_objData->GetPosition().y >= 0 && updateCount != 0)
			{
				nextState = State::NewState<Fighter_0_Idle>(_objData);
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