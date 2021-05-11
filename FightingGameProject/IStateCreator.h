#pragma once
#include "State.h"

namespace RB
{
	class IStateCreator
	{
	public:
		virtual State* Create() = 0;
	};
}