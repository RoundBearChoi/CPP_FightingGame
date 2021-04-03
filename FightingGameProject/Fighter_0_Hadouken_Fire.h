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
			animationController.status.nTransitionDelay = 8;
			animationController.status.bPlayOnce = true;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			UpdateColliders();

			if (animationController.status.nCurrentTile == 3)
			{
				if (!fired)
				{
					fired = true;
					CreateProjectile p;
					p.projectileType = ProjectileType::HADOUKEN;

					if (objData.IsFacingRight())
					{
						p.forward = { 1, 0 };
					}
					else
					{
						p.forward = { -1, 0 };
					}

					vecCreateProjectiles.push_back(p);
				}
			}

			if (updateCount >= 7 * 8)
			{
				nextState = State::NewState<Fighter_0_Hadouken_Recover>();
			}
		}

		std::vector<BoxCollider>& GetColliders() override { static std::vector<BoxCollider> vec; return vec; }
		std::vector<olc::vi2d>& GetColliderQuads() override { static std::vector<olc::vi2d> vec; return vec; }
	};
}