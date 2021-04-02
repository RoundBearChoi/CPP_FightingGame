#pragma once

namespace RB
{
	enum class ConvertedInputType
	{
		NONE,

		FORWARD,
		BACK,
		UP,
		DOWN,

		UP_FORWARD,
		DOWN_FORWARD,
		DOWN_BACK,
		UP_BACK,

		WEAK_PUNCH,
		WEAK_KICK,

		STRONG_PUNCH,
		STRONG_KICK,
	};
}