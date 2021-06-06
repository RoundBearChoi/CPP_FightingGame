#pragma once
#include "HitStopMessage.h"
#include "Updater.h"

namespace RB
{
	class ProjectilesHitStopMessage : public HitStopMessage
	{
	private:
		static Updater* _projectilesFixedUpdater;

	public:
		static void SetReceiver(Updater* fixedUpdater)
		{
			_projectilesFixedUpdater = fixedUpdater;
		}

		void Register(int32_t stopCount) override
		{
			StopCountData data;
			data.stopCount = stopCount;
			_projectilesFixedUpdater->AddStopCountQueue(data);
		}
	};
}