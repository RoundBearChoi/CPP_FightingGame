#pragma once
#include "HitStopMessage.h"
#include "Updater.h"

namespace RB
{
	class FightersHitStopMessage : public HitStopMessage
	{
	private:
		static Updater* _fightersFixedUpdater;

	public:
		static void SetReceiver(Updater* fixedUpdater)
		{
			_fightersFixedUpdater = fixedUpdater;
		}

		void Register(int32_t stopCount) override
		{
			_fightersFixedUpdater->ClearStopCount();
			_fightersFixedUpdater->AddStopCount(stopCount);
		}
	};
}