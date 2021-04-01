#pragma once

namespace RB
{
	enum class InputType
	{
		FORWARD,
		DOWN_FORWARD,
		DOWN,
		DOWN_BACK,
		BACK,
		UP_BACK,
		UP,
		UP_FORWARD,

		WEAK_PUNCH,
		STRING_PUNCH,

		WEAK_KICK,
		STRONG_KICK,
	};
}