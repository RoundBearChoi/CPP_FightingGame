#pragma once
#include "IStateCreator.h"

namespace RB
{
	class StateFactory
	{
	public:
		static StateFactory* ptr;
		StateFactory();
		~StateFactory();

		IStateCreator* Creator_Fighter_0_Idle = nullptr;
	};
}