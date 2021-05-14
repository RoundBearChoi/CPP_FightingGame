#pragma once
#include "IStateCreator.h"
#include "Fighter0Creators.h"

namespace RB
{
	class StateFactory
	{
	public:
		StateFactory();
		~StateFactory();

		IStateCreator* Creator_Fighter_0_Idle = nullptr;
		IStateCreator* Creator_Fighter_0_WalkForward = nullptr;
		IStateCreator* Creator_Fighter_0_WalkBack = nullptr;
		IStateCreator* Creator_Fighter_0_Jab = nullptr;
		IStateCreator* Creator_Fighter_0_HitReactionSide = nullptr;
		IStateCreator* Creator_Fighter_0_HitReactionUp = nullptr;
		IStateCreator* Creator_Fighter_0_Hadouken_Fire = nullptr;
		IStateCreator* Creator_Fighter_0_Hadouken_Recover = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Prep_Vertical = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Prep_Forward = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Prep_Back = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Up_Vertical = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Up_Forward = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Up_Back = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_Fall = nullptr;
		IStateCreator* Creator_Fighter_0_Jump_WeakPunch = nullptr;
		IStateCreator* Creator_Fighter_0_Crouch = nullptr;
		IStateCreator* Creator_Fighter_0_Uppercut = nullptr;
	};
}