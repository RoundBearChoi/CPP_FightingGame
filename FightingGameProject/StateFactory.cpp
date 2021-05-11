#include "StateFactory.h"

namespace RB
{
	StateFactory* StateFactory::ptr = nullptr;

	StateFactory::StateFactory()
	{

	}

	StateFactory::~StateFactory()
	{
		delete Creator_Fighter_0_Idle;
		delete Creator_Fighter_0_WalkForward;
		delete Creator_Fighter_0_WalkBack;
		delete Creator_Fighter_0_Jab;
		delete Creator_Fighter_0_HitReactionSide;
		delete Creator_Fighter_0_HitReactionUp;
		delete Creator_Fighter_0_Hadouken_Fire;
		delete Creator_Fighter_0_Hadouken_Recover;
		delete Creator_Fighter_0_Jump_Prep_Vertical;
		delete Creator_Fighter_0_Jump_Prep_Forward;
		delete Creator_Fighter_0_Jump_Prep_Back;
		delete Creator_Fighter_0_Jump_Up_Vertical;
		delete Creator_Fighter_0_Jump_Up_Forward;
		delete Creator_Fighter_0_Jump_Up_Back;
		delete Creator_Fighter_0_Jump_Fall;
		delete Creator_Fighter_0_Jump_WeakPunch;
		delete Creator_Fighter_0_Crouch;
		delete Creator_Fighter_0_Uppercut;
	}
}