#pragma once
#include <vector>
#include "GameObj.h"

namespace RB
{
	class MessageGetter
	{
	private:
		std::vector<GameObj*>* _vecObjs = nullptr;

	public:
		MessageGetter(std::vector<GameObj*>* vecObjs)
		{
			_vecObjs = vecObjs;
		}

		std::vector<CreateProjectileMessage>* GetProjectileCreationMessage(size_t _index)
		{
			std::vector<GameObj*>& vec = *_vecObjs;

			if (_index < vec.size())
			{
				return &vec[_index]->stateController->currentState->vecCreateProjectiles;
			}

			return nullptr;
		}
	};
}