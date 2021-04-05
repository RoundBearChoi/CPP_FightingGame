#pragma once
#include "ProjectileGroup.h"
#include "FightersGroup.h"

namespace RB
{
	class ProjectileCollision
	{
	public:
		static bool Collided(ProjectileGroup& projectileGroup, FightersGroup& fighterGroup, size_t& collidingProjectileIndex)
		{
			for (size_t projectileIndex = 0; projectileIndex < projectileGroup.GetObjCount(); projectileIndex++)
			{
				for (int32_t playerIndex = 0; playerIndex < 2; playerIndex++)
				{
					size_t id = fighterGroup.GetObjCreationID(playerIndex);
					size_t ownerID = projectileGroup.GetOwnerCreationID(projectileIndex);

					if (id != ownerID)
					{
						olc::vi2d projectilePos = projectileGroup.GetObjBoxColliderWorldPos(projectileIndex);

						for (int32_t bodyIndex = 0; bodyIndex <= (int32_t)BodyType::RIGHT_FOOT; bodyIndex++)
						{
							olc::vi2d bodyPos = fighterGroup.GetBodyWorldPos(playerIndex, (BodyType)bodyIndex);

							std::array<olc::vi2d, 4>projectileQuads = projectileGroup.GetObjBoxColliderWorldQuad(projectileIndex);
							std::array<olc::vi2d, 4>bodyQuads = fighterGroup.GetBodyWorldQuad(playerIndex, (BodyType)bodyIndex);

							//collision test
							if (DiagonalOverlap::yes(projectilePos, projectileQuads, bodyPos, bodyQuads))
							{
								IF_COUT{ std::cout << "projectile collision against player: " << playerIndex << std::endl; };
								IF_COUT{ std::cout << "projectile collision against body: " << bodyIndex << std::endl; };
								collidingProjectileIndex = projectileIndex;
								return true;
							}
						}
					}
				}
			}

			return false;
		}
	};
}