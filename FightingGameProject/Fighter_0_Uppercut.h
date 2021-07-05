#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Uppercut : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Uppercut()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_uppercut.png");
			animationController.SetColliderFile("BoxColliderData/Fighter_0/fighter_0_uppercut.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 4000, 200, 10, 1, 10);
			animationController.status.nTransitionDelay = 5;

			CheckCollisionMessage c0;
			CheckCollisionMessage c1;

			c0.vecBodies.push_back(BodyType::RIGHT_FOREARM);
			c0.vecBodies.push_back(BodyType::RIGHT_HAND);
			c0.animationTile = 4;
			c0.damageData.upPush = 14;
			c0.damageData.sidePush = 2;

			c1.vecBodies.push_back(BodyType::RIGHT_FOREARM);
			c1.vecBodies.push_back(BodyType::RIGHT_HAND);
			c1.animationTile = 5;
			c1.damageData.upPush = 14;
			c1.damageData.sidePush = 2;

			bodyToBodyCollisions.vecCheckCollisions.push_back(c0);
			bodyToBodyCollisions.vecCheckCollisions.push_back(c1);

			bodyToBodyCollisions.maxCollisions = 1;
		}

		void OnEnter() override
		{
			_ownerObj->objData.SetSpriteSize({ 450, 250 });
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