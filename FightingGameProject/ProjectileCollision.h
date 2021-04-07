#pragma once
#include "olcPixelGameEngine.h"
#include "ProjectileGroup.h"
#include "FightersGroup.h"
#include "DiagonalOverlap.h"

namespace RB
{
	class ProjectileCollision
	{
	public:
		static bool IsColliding(int32_t targetFighterIndex, FightersGroup& fighters, ProjectileGroup& projectiles, size_t& collidingProjectileIndex, olc::vi2d& midPoint)
		{
			for (size_t projectileIndex = 0; projectileIndex < projectiles.GetObjCount(); projectileIndex++)
			{
				size_t id = fighters.GetObjCreationID(targetFighterIndex);
				size_t ownerID = projectiles.GetOwnerCreationID(projectileIndex);

				if (id != ownerID)
				{
					olc::vi2d projectilePos = projectiles.GetObjBoxColliderWorldPos(projectileIndex);
					std::array<olc::vi2d, 4>projectileQuads = projectiles.GetObjBoxColliderWorldQuad(projectileIndex);

					//check all body parts
					for (int32_t bodyIndex = 0; bodyIndex <= (int32_t)BodyType::RIGHT_FOOT; bodyIndex++)
					{
						olc::vi2d bodyPos = fighters.GetBodyWorldPos(targetFighterIndex, (BodyType)bodyIndex);
						std::array<olc::vi2d, 4>bodyQuads = fighters.GetBodyWorldQuad(targetFighterIndex, (BodyType)bodyIndex);

						//collision test
						if (DiagonalOverlap::Overlapping(projectilePos, projectileQuads, bodyPos, bodyQuads))
						{
							IF_COUT{ std::cout << "projectile collision against player: " << targetFighterIndex << std::endl; };
							IF_COUT{ std::cout << "projectile collision against body: " << bodyIndex << std::endl; };

							collidingProjectileIndex = projectileIndex;

							olc::vf2d distance = bodyPos - projectilePos;
							distance *= 0.5f;
							olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));
							midPoint = rounded + projectilePos;

							return true;
						}
					}
				}
			}

			return false;
		}
	};
}