#pragma once
#include "Updater.h"

namespace RB
{
	class ProjectilesFixedUpdater : public Updater
	{
	private:
		ObjGroup* _projectilesGroup = nullptr;

	public:
		ProjectilesFixedUpdater(ObjGroup* projectilesGroup)
		{
			_projectilesGroup = projectilesGroup;
		}

		void CustomUpdate() override
		{
			std::vector<GameObj*>& vecObjs = *_projectilesGroup->GetVecObjs();

			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					State* state = vecObjs[i]->stateController->currentState;

					if (state != nullptr)
					{
						state->RunUpdateProcess();
					}
				}
			}

			UpdateUpdateCount();
		}
	};
}