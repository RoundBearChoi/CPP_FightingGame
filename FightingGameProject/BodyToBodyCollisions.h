#pragma once
#include <vector>
#include <stdint.h>
#include "CheckCollisionMessage.h"
#include "AnimationController.h"

namespace RB
{
	class BodyToBodyCollisions
	{
	public:
		int32_t currentCollisionCount = 0;
		int32_t maxCollisions = 0;
		std::vector<CheckCollisionMessage> vecCheckCollisions;

		CheckCollisionMessage* GetCheckCollisionMessage(AnimationController& animationController)
		{
			for (size_t i = 0; i < vecCheckCollisions.size(); i++)
			{
				if (vecCheckCollisions[i].animationTile == animationController.status.nCurrentTile)
				{
					return &vecCheckCollisions[i];
				}
				else
				{
					int n = 0;
				}
			}

			return nullptr;
		}
	};
}