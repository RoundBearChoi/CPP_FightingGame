#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Jump_WeakPunch : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jump_WeakPunch()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jump_weakpunch.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_jump_weakpunch.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 400, 200, 1, 1, 1);
			animationController.status.bPlayOnce = true;

			CheckCollisionMessage c0;

			c0.vecBodies.push_back(BodyType::LEFT_HAND);
			c0.vecBodies.push_back(BodyType::LEFT_KNEE);
			c0.vecBodies.push_back(BodyType::LEFT_LOWERLEG);
			c0.animationTile = 0;

			vecCheckCollisions.push_back(c0);

			maxBodyCollisions = 1;
		}

		void OnEnter() override
		{
			_objData->SetSpriteSize({ 420, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			if (_objData->GetPosition().y >= 0 && updateCount != 0)
			{
				nextState = State::NewState<Fighter_0_Idle>(_objData);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}