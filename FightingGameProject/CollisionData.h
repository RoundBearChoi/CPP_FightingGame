#pragma once
#include <vector>
#include "GameObj.h"
#include "CheckCollisionMessage.h"

namespace RB
{
	class CollisionData
	{
	private:
		std::vector<GameObj*>* _vecObjs = nullptr;

	public:
		CollisionData(std::vector<GameObj*>* vecObjs)
		{
			_vecObjs = vecObjs;
		}

		CheckCollisionMessage* GetCheckCollisionMessage(size_t index)
		{
			std::vector<GameObj*>& vec = *_vecObjs;

			if (index < vec.size())
			{
				if (vec[index]->stateController->currentState != nullptr)
				{
					if (vec[index]->stateController->currentState->vecCheckCollisions.size() > 0)
					{
						return vec[index]->stateController->currentState->GetCollisionStatus();
					}
				}
			}

			return nullptr;
		}
	};
}