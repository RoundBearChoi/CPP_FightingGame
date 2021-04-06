#pragma once
#include "DiagonalOverlap.h"

namespace RB
{
	class BodyCollision
	{
	public:
		static bool IsColliding(GameObj& me, BodyType& myBody, GameObj& enemy, BodyType& enemyBody)
		{
			olc::vi2d p1Center = me.stateController.currentState->GetColliderWorldPos(myBody, me.objData);
			std::array<olc::vi2d, 4> p1Quads = me.stateController.currentState->GetColliderQuadsWorldPos(myBody, me.objData);

			olc::vi2d p2Center = enemy.stateController.currentState->GetColliderWorldPos(enemyBody, enemy.objData);
			std::array<olc::vi2d, 4> p2Quads = enemy.stateController.currentState->GetColliderQuadsWorldPos(enemyBody, enemy.objData);

			if (DiagonalOverlap::yes(p1Center, p1Quads, p2Center, p2Quads))
			{
				return true;
			}

			return false;
		}
	};
}