#pragma once
#include "DiagonalOverlap.h"
#include "BodyType.h"

namespace RB
{
	class BodyPartCollision
	{
	public:
		static bool IsColliding(int32_t attackerIndex, FightersGroup& fighters, olc::vi2d& resultMid, DamageData& damageData)
		{
			int32_t targetIndex = 0;

			if (attackerIndex == 0)
			{
				targetIndex = 1;
			}
			else if (attackerIndex == 1)
			{
				targetIndex = 0;
			}

			CollisionQueue* collisionQueue = fighters.GetCollisionQueue(attackerIndex);

			if (collisionQueue)
			{
				if (*fighters.CollisionCount(attackerIndex) < fighters.MaxCollisions(attackerIndex))
				{
					for (BodyType& b : collisionQueue->vecBodies)
					{
						olc::vi2d attackPos = fighters.GetBodyWorldPos(attackerIndex, b);
						std::array<olc::vi2d, 4> attackQuad = fighters.GetBodyWorldQuad(attackerIndex, b);

						std::cout << "attackpos: " << attackPos << std::endl;

						olc::vi2d targetPos = fighters.GetBodyWorldPos(targetIndex, BodyType::HEAD);
						std::array<olc::vi2d, 4> targetQuad = fighters.GetBodyWorldQuad(targetIndex, BodyType::HEAD);

						if (DiagonalOverlap::Overlapping(attackPos, attackQuad, targetPos, targetQuad))
						{
							IF_COUT{ std::cout << "overlap!" << std::endl; };
							IF_COUT{ std::cout << "attacker body index: " << (int32_t)b << std::endl; };

							olc::vf2d distance = targetPos - attackPos;
							distance *= 0.5f;
							olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));
							resultMid = attackPos + rounded;

							int32_t& collisionCount = *fighters.CollisionCount(attackerIndex);
							collisionCount++;

							damageData = collisionQueue->damageData;

							return true;
						}
					}
				}

				IF_COUT{ std::cout << "collision check processed" << std::endl; };
			}

			return false;
		}
	};
}