#pragma once
#include <stdint.h>

namespace RB
{
	class SlowMotionMessage
	{
	public:
		size_t updateCount = 0;
		int32_t interval = 0;
		int32_t maxCount = 0;

		bool SkipUpdate()
		{
			if (updateCount != 0 && updateCount % interval == 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	};
}