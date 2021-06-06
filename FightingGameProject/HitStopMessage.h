#pragma once
#include <stdint.h>

namespace RB
{
	class HitStopMessage
	{
	public:
		virtual void Register(int32_t stopCount) = 0;
	};
}