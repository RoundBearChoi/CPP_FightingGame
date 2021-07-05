#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Jab : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Jab()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_jab.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_jab.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 3;

			CheckCollisionMessage c0;
			CheckCollisionMessage c1;

			c0.vecBodies.push_back(BodyType::LEFT_FOREARM);
			c0.vecBodies.push_back(BodyType::LEFT_HAND);
			c0.animationTile = 2;

			c1.vecBodies.push_back(BodyType::LEFT_FOREARM);
			c1.vecBodies.push_back(BodyType::LEFT_HAND);
			c1.animationTile = 3;

			bodyToBodyCollisions.vecCheckCollisions.push_back(c0);
			bodyToBodyCollisions.vecCheckCollisions.push_back(c1);

			bodyToBodyCollisions.maxCollisions = 1;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate() override
		{
			UpdateColliderParts();

			size_t end = ((size_t)animationController.GetTotalTiles() - (size_t)1) * (size_t)animationController.status.nTransitionDelay;

			if (stateUpdateCount >= end)
			{
				nextState = State::NewState<Fighter_0_Idle>(_ownerObj);
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}