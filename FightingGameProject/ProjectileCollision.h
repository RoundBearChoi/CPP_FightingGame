#pragma once
#include "olcPixelGameEngine.h"
#include "ObjGroup.h"
#include "DiagonalOverlap.h"

namespace RB
{
	class ProjectileCollision
	{
	public:
		static bool IsColliding(int32_t targetFighterIndex, ObjGroup& fighters, ObjGroup& projectiles, size_t& resultProjectileIndex, olc::vi2d& resultMidPoint)
		{
			for (size_t projectileIndex = 0; projectileIndex < projectiles.GetObjCount(); projectileIndex++)
			{
				size_t id = fighters.GetObjCreationID(targetFighterIndex);
				size_t ownerID = projectiles.GetOwnerCreationID(projectileIndex);

				if (id != ownerID)
				{
					olc::vi2d projectilePos = projectiles.colliderData->GetBoxColliderWorldPos(projectileIndex);
					std::array<olc::vi2d, 4>projectileQuads = projectiles.GetObjBoxColliderWorldQuad(projectileIndex);

					//check all body parts
					for (int32_t bodyIndex = 0; bodyIndex <= (int32_t)BodyType::RIGHT_FOOT; bodyIndex++)
					{
						olc::vi2d bodyPos = fighters.GetBodyWorldPos(targetFighterIndex, (BodyType)bodyIndex);
						std::array<olc::vi2d, 4>bodyQuads = fighters.GetBodyWorldQuad(targetFighterIndex, (BodyType)bodyIndex);

						if (DiagonalOverlap::Overlapping(projectilePos, projectileQuads, bodyPos, bodyQuads))
						{
							IF_COUT{ std::cout << "projectile collision against player: " << targetFighterIndex << std::endl; };
							IF_COUT{ std::cout << "projectile collision against body: " << bodyIndex << std::endl; };

							resultProjectileIndex = projectileIndex;

							olc::vf2d distance = bodyPos - projectilePos;
							distance *= 0.5f;
							olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));
							resultMidPoint = rounded + projectilePos;

							return true;
						}
					}
				}
			}

			return false;
		}
	};
}