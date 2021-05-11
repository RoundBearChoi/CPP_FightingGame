#pragma once
#include "IStateCreator.h"
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_HitReaction_Side.h"
#include "Fighter_0_HitReaction_Up.h"
#include "Fighter_0_Hadouken_Fire.h"
#include "Fighter_0_Hadouken_Recover.h"
#include "Fighter_0_Jump_Prep_Vertical.h"
#include "Fighter_0_Jump_Prep_Forward.h"
#include "Fighter_0_Jump_Prep_Back.h"
#include "Fighter_0_Jump_Up_Vertical.h"
#include "Fighter_0_Jump_Up_Forward.h"
#include "Fighter_0_Jump_Up_Back.h"
#include "Fighter_0_Jump_Fall.h"
#include "Fighter_0_Jump_WeakPunch.h"

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

	class CREATOR_Fighter_0_HitReactionSide : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_HitReaction_Side();
		}
	};

	class CREATOR_Fighter_0_HitReactionUp : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_HitReaction_Up();
		}
	};

	class CREATOR_Fighter_0_Hadouken_Fire : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Hadouken_Fire();
		}
	};

	class CREATOR_Fighter_0_Hadouken_Recover : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Hadouken_Recover();
		}
	};

	class CREATOR_Fighter_0_Jump_Prep_Vertical : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Prep_Vertical();
		}
	};

	class CREATOR_Fighter_0_Jump_Prep_Forward : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Prep_Forward();
		}
	};

	class CREATOR_Fighter_0_Jump_Prep_Back : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Prep_Back();
		}
	};

	class CREATOR_Fighter_0_Jump_Up_Vertical : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Up_Vertical();
		}
	};

	class CREATOR_Fighter_0_Jump_Up_Forward : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Up_Forward();
		}
	};

	class CREATOR_Fighter_0_Jump_Up_Back : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Up_Back();
		}
	};

	class CREATOR_Fighter_0_Jump_Fall : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_Fall();
		}
	};

	class CREATOR_Fighter_0_Jump_WeakPunch : public IStateCreator
	{
	public:
		State* Create() override
		{
			return new Fighter_0_Jump_WeakPunch();
		}
	};
}