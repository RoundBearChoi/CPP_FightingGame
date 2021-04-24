#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Hadouken_Recover;

	class Fighter_0_Hadouken_Fire : public State
	{
	private:
		bool fired = false;

	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Fighter_0_Hadouken_Fire()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_hadouken_fire.png");
			animationController.SetColliderFile("Fighter_0/fighter_0_hadouken_fire.collider");

			animationController.SetParams(SpriteType::FIGHTER_0, 1600, 200, 4, 1, 4);
			animationController.status.nTransitionDelay = 5;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void OnUpdate(ObjData& objData, GameData& gameData) override
		{
			UpdateColliderParts();

			if (animationController.status.nCurrentTile == 3)
			{
				if (!fired)
				{
					fired = true;
					CreateProjectile p;
					p.projectileType = ProjectileType::HADOUKEN;

					p.startPos = objData.GetPosition() + olc::vi2d(0, -105);

					if (objData.IsFacingRight())
					{
						p.forward = { 1, 0 };
						p.startPos += olc::vi2d(55, 0);
					}
					else
					{
						p.forward = { -1, 0 };
						p.startPos += olc::vi2d(-55, 0);
					}

					p.ownerObjCreationID = objData.GetCreationID();

					vecCreateProjectiles.push_back(p);
				}
			}

			int32_t targetdelay = 8;
			size_t end = (size_t)animationController.status.nTransitionDelay * targetdelay;

			if (updateCount >= end)
			{
				nextState = State::NewState<Fighter_0_Hadouken_Recover>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}