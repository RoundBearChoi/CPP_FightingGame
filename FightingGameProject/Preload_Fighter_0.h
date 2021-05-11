#pragma once
#include "StateFactory.h"
#include "Fighter0Creators.h"

namespace RB
{
	class Preload_Fighter_0
	{
	private:
		template<class T>
		T* Setup()
		{
			T* creator = new T();
			State* newState = creator->Create();
			newState->UpdateColliderParts();
			delete newState;

			return creator;
		}

	public:
		Preload_Fighter_0()
		{
			StateFactory::ptr->Creator_Fighter_0_Idle = Setup<CREATOR_Fighter_0_Idle>();
			StateFactory::ptr->Creator_Fighter_0_WalkForward = Setup<CREATOR_Fighter_0_WalkForward>();
			StateFactory::ptr->Creator_Fighter_0_WalkBack = Setup<CREATOR_Fighter_0_WalkBack>();
			StateFactory::ptr->Creator_Fighter_0_Jab = Setup<CREATOR_Fighter_0_Jab>();
			StateFactory::ptr->Creator_Fighter_0_HitReactionSide = Setup<CREATOR_Fighter_0_HitReactionSide>();
			StateFactory::ptr->Creator_Fighter_0_HitReactionUp = Setup<CREATOR_Fighter_0_HitReactionUp>();
			StateFactory::ptr->Creator_Fighter_0_Hadouken_Fire = Setup<CREATOR_Fighter_0_Hadouken_Fire>();
			StateFactory::ptr->Creator_Fighter_0_Hadouken_Recover = Setup<CREATOR_Fighter_0_Hadouken_Recover>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Prep_Vertical = Setup<CREATOR_Fighter_0_Jump_Prep_Vertical>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Prep_Forward = Setup<CREATOR_Fighter_0_Jump_Prep_Forward>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Prep_Back = Setup<CREATOR_Fighter_0_Jump_Prep_Back>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Up_Vertical = Setup<CREATOR_Fighter_0_Jump_Up_Vertical>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Up_Forward = Setup<CREATOR_Fighter_0_Jump_Up_Forward>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Up_Back = Setup<CREATOR_Fighter_0_Jump_Up_Back>();
			StateFactory::ptr->Creator_Fighter_0_Jump_Fall = Setup<CREATOR_Fighter_0_Jump_Fall>();
			StateFactory::ptr->Creator_Fighter_0_Jump_WeakPunch = Setup<CREATOR_Fighter_0_Jump_WeakPunch>();
			StateFactory::ptr->Creator_Fighter_0_Crouch = Setup<CREATOR_Fighter_0_Crouch>();
			StateFactory::ptr->Creator_Fighter_0_Uppercut = Setup<CREATOR_Fighter_0_Uppercut>();
		}
	};
}