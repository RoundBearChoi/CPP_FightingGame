#pragma once
#include <stdint.h>

namespace RB
{
	class StopCountData
	{
	public:
		bool oneFrameSkipped = false;
		int32_t stopCount = 0;
	};
}