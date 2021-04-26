#pragma once
#include "DiagonalOverlap.h"
#include "BodyType.h"

namespace RB
{
	class BodyPartCollision
	{
	public:
		static bool IsColliding(int32_t attackerIndex, ObjGroup& fighters, olc::vi2d& resultMid, DamageData& damageData)
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

			CheckCollisionMessage* message = fighters.GetCollisionQueue(attackerIndex);

			if (message)
			{
				if (fighters.GetCollisionCount(attackerIndex) < fighters.MaxCollisions(attackerIndex))
				{
					for (BodyType& b : message->vecBodies)
					{
						olc::vi2d attackPos = fighters.GetBodyWorldPos(attackerIndex, b);
						std::array<olc::vi2d, 4> attackQuad = fighters.GetBodyWorldQuad(attackerIndex, b);

						std::cout << "attackpos: " << attackPos << std::endl;

						//check all body parts
						for (int32_t i = 0; i <= (int32_t)BodyType::RIGHT_FOOT; i++)
						{
							olc::vi2d targetPos = fighters.GetBodyWorldPos(targetIndex, (BodyType)i);
							std::array<olc::vi2d, 4> targetQuad = fighters.GetBodyWorldQuad(targetIndex, (BodyType)i);

							if (DiagonalOverlap::Overlapping(attackPos, attackQuad, targetPos, targetQuad))
							{
								IF_COUT{ std::cout << "overlap!" << std::endl; };
								IF_COUT{ std::cout << "attacker body index: " << (int32_t)b << std::endl; };

								olc::vf2d distance = targetPos - attackPos;
								distance *= 0.5f;
								olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));
								resultMid = attackPos + rounded;

								fighters.AddCollisionCount(attackerIndex);
								damageData = message->damageData;

								return true;
							}
						}
					}
				}

				IF_COUT{ std::cout << "collision check processed" << std::endl; };
			}

			return false;
		}
	};
}