#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_HitReaction_Up : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_HitReaction_Up()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_hitreaction_up.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_hitreaction_up.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 1600, 200, 4, 1, 4);
			animationController.status.nTransitionDelay = 7;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}