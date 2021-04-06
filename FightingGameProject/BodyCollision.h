#pragma once
#include "DiagonalOverlap.h"
#include "BodyType.h"

namespace RB
{
	class BodyCollision
	{
	public:
		static bool IsColliding(int32_t attackerIndex, FightersGroup& fighters)
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
				if (!collisionQueue->processed)
				{
					collisionQueue->processed = true;

					for (BodyType& b : collisionQueue->vecBodies)
					{
						olc::vi2d targetPos = fighters.GetBodyWorldPos(targetIndex, BodyType::HEAD);
						std::array<olc::vi2d, 4> targetQuad = fighters.GetBodyWorldQuad(targetIndex, BodyType::HEAD);

						olc::vi2d attackPos = fighters.GetBodyWorldPos(attackerIndex, b);
						std::array<olc::vi2d, 4> attackQuad = fighters.GetBodyWorldQuad(attackerIndex, b);

						if (DiagonalOverlap::Overlapping(attackPos, attackQuad, targetPos, targetQuad))
						{
							IF_COUT{ std::cout << "overlap!" << std::endl; };
							IF_COUT{ std::cout << "attacker body index: " << (int32_t)b << std::endl; };
							return true;
						}
					}

					IF_COUT{ std::cout << "collision check processed" << std::endl; };
				}
			}

			return false;
		}
	};
}