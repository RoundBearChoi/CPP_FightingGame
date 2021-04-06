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
			animationController.SetColliderFile("Fighter_0/fighter_0_jab.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 5;

			CollisionQueue c0;
			CollisionQueue c1;

			c0.vecBodies.push_back(BodyType::LEFT_FOREARM);
			c0.vecBodies.push_back(BodyType::LEFT_HAND);
			c0.frame = 2;

			c1.vecBodies.push_back(BodyType::LEFT_FOREARM);
			c1.vecBodies.push_back(BodyType::LEFT_HAND);
			c1.frame = 3;

			vecCollisionStatus.push_back(c0);
			vecCollisionStatus.push_back(c1);
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliders();

			if (objData.GetAnimationIndex() == 5)
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}