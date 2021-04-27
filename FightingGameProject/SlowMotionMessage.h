#pragma once
#include <stdint.h>
#include "SlowMotionGroupType.h"

namespace RB
{
	class SlowMotionMessage
	{
	public:
		SlowMotionGroupType groupType = SlowMotionGroupType::ALL;
		size_t updateCount = 0;
		int32_t interval = 0;
		int32_t maxCount = 0;

		bool SkipUpdate(SlowMotionGroupType _groupType)
		{
			if (groupType == _groupType)
			{
				if (updateCount != 0 && updateCount % interval == 0)
				{
					return false;
				}

				updateCount++;

				return true;
			}
		}
	};
}