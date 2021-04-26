#pragma once
#include <stdint.h>
#include "SlowMotionGroupType.h"

namespace RB
{
	class SlowMotionMessage
	{
	public:
		SlowMotionGroupType groupType = SlowMotionGroupType::ALL;
		int32_t interval = 0;
		int32_t maxCount = 0;
	};
}