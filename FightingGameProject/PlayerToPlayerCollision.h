#pragma once
#include "GameObj.h"
#include "MeleeCollisionResult.h"
#include "DiagonalOverlap.h"

namespace RB
{
	class PlayerToPlayerCollision
	{
	private:
		ObjBase* _fighter0 = nullptr;
		ObjBase* _fighter1 = nullptr;

	public:
		PlayerToPlayerCollision(ObjBase* fighter0, ObjBase* fighter1)
		{
			_fighter0 = fighter0;
			_fighter1 = fighter1;
		}

		MeleeCollisionResult Fighter0HitsFighter1()
		{
			CheckCollisionMessage* fighter0_Message = _fighter0->GetCurrentState()->GetCheckCollisionMessage();

			if (fighter0_Message != nullptr)
			{
				MeleeCollisionResult result = GetCollisionResult(fighter0_Message, _fighter0, _fighter1);

				if (result.isCollided)
				{
					return result;
				}
			}

			MeleeCollisionResult noCollision;
			return noCollision;
		}

		MeleeCollisionResult Fighter1HitsFighter0()
		{
			CheckCollisionMessage* fighter1_Message = _fighter1->GetCurrentState()->GetCheckCollisionMessage();

			if (fighter1_Message != nullptr)
			{
				MeleeCollisionResult result = GetCollisionResult(fighter1_Message, _fighter1, _fighter0);

				if (result.isCollided)
				{
					return result;
				}
			}

			MeleeCollisionResult noCollision;
			return noCollision;
		}

		MeleeCollisionResult GetCollisionResult(CheckCollisionMessage* attackerMessage, ObjBase* attacker, ObjBase* target)
		{
			if (attacker->GetCurrentState()->bodyToBodyCollisions.currentCollisionCount < attacker->GetCurrentState()->bodyToBodyCollisions.maxCollisions)
			{
				for (BodyType& b : attackerMessage->vecBodies)
				{
					olc::vi2d attackPos = attacker->GetBodyWorldPos(b);
					std::array<olc::vi2d, 4> attackQuad = attacker->GetBodyWorldQuad(b);

					IF_COUT{ std::cout << "attackpos: " << attackPos << std::endl; };
					
					//check all body parts
					for (int32_t i = 0; i <= (int32_t)BodyType::RIGHT_FOOT; i++)
					{
						olc::vi2d targetPos = target->GetBodyWorldPos((BodyType)i);
						std::array<olc::vi2d, 4> targetQuad = target->GetBodyWorldQuad((BodyType)i);

						if (DiagonalOverlap::Overlapping(attackPos, attackQuad, targetPos, targetQuad))
						{
							IF_COUT{ std::cout << "attacker body index: " << (int32_t)b << std::endl; };

							olc::vf2d distance = targetPos - attackPos;
							distance *= 0.5f;
							olc::vi2d rounded((int32_t)std::round(distance.x), (int32_t)std::round(distance.y));

							MeleeCollisionResult result;
							result.isCollided = true;
							result.midPoint = attackPos + rounded;
							result.damageData = attackerMessage->damageData;

							attacker->GetCurrentState()->bodyToBodyCollisions.currentCollisionCount++;

							return result;
						}
					}
				}
			}

			MeleeCollisionResult noCollision;
			return noCollision;
		}
	};
}