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
			//skip on the next frame
			if (updateCount != 0 && updateCount % interval == 1)
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