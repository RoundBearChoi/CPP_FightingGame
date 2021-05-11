#pragma once
#include "IStateCreator.h"
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_Jab.h"

namespace RB
{
	class CREATOR_Fighter_0_Idle : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Idle();
		}
	};

	class CREATOR_Fighter_0_WalkForward : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_WalkForward();
		}
	};

	class CREATOR_Fighter_0_WalkBack : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_WalkBack();
		}
	};

	class CREATOR_Fighter_0_Jab : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jab();
		}
	};
}