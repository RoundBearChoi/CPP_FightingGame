#pragma once
#include <stdint.h>
#include "InputType.h"

namespace RB
{
	class InputElement
	{
	public:
		InputType inputType;
		size_t updateCount = 0;

		InputElement(InputType _inputType)
		{
			inputType = _inputType;
		}
	};
}