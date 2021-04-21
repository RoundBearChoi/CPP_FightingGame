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
			animationController.SetColliderFile("Fighter_0/fighter_0_uppercut.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 4000, 200, 10, 1, 10);
			animationController.status.nTransitionDelay = 5;

			CollisionQueue c0;
			CollisionQueue c1;

			c0.vecBodies.push_back(BodyType::RIGHT_FOREARM);
			c0.vecBodies.push_back(BodyType::RIGHT_HAND);
			c0.animationTile = 4;
			c0.damageData.upPush = 15;

			c1.vecBodies.push_back(BodyType::RIGHT_FOREARM);
			c1.vecBodies.push_back(BodyType::RIGHT_HAND);
			c1.animationTile = 5;
			c1.damageData.upPush = 13;
			c1.damageData.sidePush = 15;

			vecCollisionStatus.push_back(c0);
			vecCollisionStatus.push_back(c1);

			maxBodyCollisions = 1;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 450, 250 });
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			int32_t end = (animationController.GetTotalTiles() - 1) * animationController.status.nTransitionDelay;

			if (updateCount >= end)
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}