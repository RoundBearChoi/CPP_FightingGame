#pragma once
#include <vector>
#include "GameObj.h"
#include "PlayerToProjectileCollisionResult.h"

namespace RB
{
	class PlayerToProjectileCollision
	{
	private:
		std::vector<GameObj*>* _vecFighters = nullptr;
		std::vector<GameObj*>* _vecProjectiles = nullptr;

	public:
		PlayerToProjectileCollision(std::vector<GameObj*>* fighters, std::vector<GameObj*>* projectiles)
		{
			_vecFighters = fighters;
			_vecProjectiles = projectiles;
		}

		PlayerToProjectileCollisionResult FighterCollidesWithProjectile(size_t fighterIndex)
		{
			std::vector<GameObj*>& projectiles = *_vecProjectiles;
			std::vector<GameObj*>& fighters = *_vecFighters;

			for (size_t projectileIndex = 0; projectileIndex < projectiles.size(); projectileIndex++)
			{
				size_t id = fighters[fighterIndex]->objData.GetCreationID();
				size_t ownerID = projectiles[projectileIndex]->objData.GetOwnerID();

				if (id != ownerID)
				{
					olc::vi2d projectilePos = projectiles[projectileIndex]->GetBoxColliderWorldPos();
					std::array<olc::vi2d, 4>projectileQuads = projectiles[projectileIndex]->GetBoxColliderWorldQuad();

					//check all body parts
					for (int32_t bodyIndex = 0; bodyIndex <= (int32_t)BodyType::RIGHT_FOOT; bodyIndex++)
					{
						olc::vi2d bodyPos = fighters[fighterIndex]->GetBodyWorldPos((BodyType)bodyIndex);
						std::array<olc::vi2d, 4>bodyQuads = fighters[fighterIndex]->GetBodyWorldQuad((BodyType)bodyIndex);

						if (DiagonalOverlap::Overlapping(projectilePos, projectileQuads, bodyPos, bodyQuads))
						{
							PlayerToProjectileCollisionResult result;
							result.isCollided = true;

							IF_COUT{ std::cout << "projectile collision against player: " << 0 << std::endl; };
							IF_COUT{ std::cout << "projectile collision against body: " << bodyIndex << std::endl; };

							result.projectileIndex = projectileIndex;

							olc::vf2d distance = bodyPos - projectilePos;
							distance *= 0.5f;
							olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));
							result.midPoint = rounded + projectilePos;

							return result;
						}
					}
				}
			}

			PlayerToProjectileCollisionResult noCollision;
			return noCollision;
		}

		PlayerToProjectileCollisionResult Fighter1_CollidesWithProjectile()
		{
			PlayerToProjectileCollisionResult noCollision;
			return noCollision;
		}
	};
}