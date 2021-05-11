#pragma once
#include "IStateCreator.h"
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"

namespace RB
{
	class Fighter_0_Idle_Creator : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Idle();
		}
	};

	class Fighter_0_WalkForward_Creator : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_WalkForward();
		}
	};
}