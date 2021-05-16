#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;
	class Fighter_0_Uppercut;

	class Fighter_0_Crouch : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Crouch()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_crouch.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_crouch.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 400, 200, 1, 1, 1);
		}

		void OnEnter() override
		{
			_objData->SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			PlayerInput p = PlayerInput::Get(_objData->GetPlayerType());

			if (p.strongpunch)
			{
				nextState = State::NewState<Fighter_0_Uppercut>(_objData);
			}
			else
			{
				if (!p.down)
				{
					nextState = State::NewState<Fighter_0_Idle>(_objData);
				}
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}