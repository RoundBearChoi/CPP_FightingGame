#pragma once
#include <stdint.h>
#include "InputType.h"

namespace RB
{
	class InputElement
	{
	public:
		InputType inputType;
		int32_t frameCount = 0;
	};
}