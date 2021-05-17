#pragma once
#include "DiagonalOverlap.h"
#include "BodyType.h"

namespace RB
{
	class BodyPartToBodyPartCollision
	{
	private:
		ObjGroup* _fighters = nullptr;

	public:
		BodyPartToBodyPartCollision(ObjGroup* fighters)
		{
			_fighters = fighters;
		}

		bool IsColliding(int32_t attackerIndex, olc::vi2d& resultMid, DamageData& damageData)
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

			CheckCollisionMessage* message = _fighters->collisionData->GetCheckCollisionMessage(attackerIndex);

			if (message)
			{
				if (_fighters->collisionData->GetCollisionCount(attackerIndex) < _fighters->collisionData->GetMaxCollisions(attackerIndex))
				{
					for (BodyType& b : message->vecBodies)
					{
						olc::vi2d attackPos = _fighters->colliderData->GetBodyWorldPos(attackerIndex, b);
						std::array<olc::vi2d, 4> attackQuad = _fighters->colliderData->GetBodyWorldQuad(attackerIndex, b);

						std::cout << "attackpos: " << attackPos << std::endl;

						//check all body parts
						for (int32_t i = 0; i <= (int32_t)BodyType::RIGHT_FOOT; i++)
						{
							olc::vi2d targetPos = _fighters->colliderData->GetBodyWorldPos(targetIndex, (BodyType)i);
							std::array<olc::vi2d, 4> targetQuad = _fighters->colliderData->GetBodyWorldQuad(targetIndex, (BodyType)i);

							if (DiagonalOverlap::Overlapping(attackPos, attackQuad, targetPos, targetQuad))
							{
								IF_COUT{ std::cout << "overlap!" << std::endl; };
								IF_COUT{ std::cout << "attacker body index: " << (int32_t)b << std::endl; };

								olc::vf2d distance = targetPos - attackPos;
								distance *= 0.5f;
								olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));
								resultMid = attackPos + rounded;

								_fighters->collisionData->AddCollisionCount(attackerIndex);
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