#include "StateFactory.h"

namespace RB
{
	StateFactory* StateFactory::ptr = nullptr;

	StateFactory::StateFactory()
	{
		Creator_Fighter_0_Idle = new CREATOR_Fighter_0_Idle();
		Creator_Fighter_0_WalkForward = new CREATOR_Fighter_0_WalkForward();
		Creator_Fighter_0_WalkBack = new CREATOR_Fighter_0_WalkBack();
		Creator_Fighter_0_Jab = new CREATOR_Fighter_0_Jab();
		Creator_Fighter_0_HitReactionSide = new CREATOR_Fighter_0_HitReactionSide();
		Creator_Fighter_0_HitReactionUp = new CREATOR_Fighter_0_HitReactionUp();
		Creator_Fighter_0_Hadouken_Fire = new CREATOR_Fighter_0_Hadouken_Fire();
		Creator_Fighter_0_Hadouken_Recover = new CREATOR_Fighter_0_Hadouken_Recover();
		Creator_Fighter_0_Jump_Prep_Vertical = new CREATOR_Fighter_0_Jump_Prep_Vertical();
		Creator_Fighter_0_Jump_Prep_Forward = new CREATOR_Fighter_0_Jump_Prep_Forward();
		Creator_Fighter_0_Jump_Prep_Back = new CREATOR_Fighter_0_Jump_Prep_Back();
		Creator_Fighter_0_Jump_Up_Vertical = new CREATOR_Fighter_0_Jump_Up_Vertical();
		Creator_Fighter_0_Jump_Up_Forward = new CREATOR_Fighter_0_Jump_Up_Forward();
		Creator_Fighter_0_Jump_Up_Back = new CREATOR_Fighter_0_Jump_Up_Back();
		Creator_Fighter_0_Jump_Fall = new CREATOR_Fighter_0_Jump_Fall();
		Creator_Fighter_0_Jump_WeakPunch = new CREATOR_Fighter_0_Jump_WeakPunch();
		Creator_Fighter_0_Crouch = new CREATOR_Fighter_0_Crouch();
		Creator_Fighter_0_Uppercut = new CREATOR_Fighter_0_Uppercut();
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