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
			if (_stopCount > 0)
			{
				_stopCount--;
			}
			else
			{
				DoUpdate();
			}
		}

		void DoUpdate()
		{
			std::vector<ObjBase*>& vecObjs = *_projectilesGroup->GetVecObjs();

			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					State* state = vecObjs[i]->GetCurrentState();

					if (state != nullptr)
					{
						state->RunUpdateProcess();
					}
				}
			}

			_projectilesGroup->UpdateSpriteTileIndex();

			ProcessStopCounts();
			UpdateUpdateCount();
		}
	};
}