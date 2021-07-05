#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Jump_Up_Back;

	class Fighter_0_Jump_Prep_Back : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_Prep_Back()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_prep_back.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_jump_prep_back.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 400, 200, 1, 1, 1);
			animationController.status.nTransitionDelay = 4;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			if (stateUpdateCount >= 3)
			{
				nextState = State::NewState<Fighter_0_Jump_Up_Back>(_ownerObj);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}