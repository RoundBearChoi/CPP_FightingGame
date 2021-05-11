#pragma once
//#include "Fighter_0_Idle.h"
//#include "Fighter_0_WalkForward.h"
//#include "Fighter_0_WalkBack.h"
//#include "Fighter_0_Jab.h"
//#include "Fighter_0_HitReaction_Side.h"
//#include "Fighter_0_HitReaction_Up.h"
//#include "Fighter_0_Hadouken_Fire.h"
//#include "Fighter_0_Hadouken_Recover.h"
//#include "Fighter_0_Jump_Prep_Vertical.h"
//#include "Fighter_0_Jump_Prep_Forward.h"
//#include "Fighter_0_Jump_Prep_Back.h"
//#include "Fighter_0_Jump_Up_Vertical.h"
//#include "Fighter_0_Jump_Up_Forward.h"
//#include "Fighter_0_Jump_Up_Back.h"
#include "Fighter_0_Jump_Fall.h"
#include "Fighter_0_Jump_WeakPunch.h"
#include "Fighter_0_Crouch.h"
#include "Fighter_0_Uppercut.h"

#include "StateFactory.h"
#include "Fighter0Creators.h"

namespace RB
{
	class Preload_Fighter_0
	{
	private:
		template<class T>
		void Load()
		{
			T state;
			state.UpdateColliderParts();
		}

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
			Setup<CREATOR_Fighter_0_WalkForward>();
			Setup<CREATOR_Fighter_0_WalkBack>();
			Setup<CREATOR_Fighter_0_Jab>();
			Setup<CREATOR_Fighter_0_HitReactionSide>();
			Setup<CREATOR_Fighter_0_HitReactionUp>();
			Setup<CREATOR_Fighter_0_Hadouken_Fire>();
			Setup<CREATOR_Fighter_0_Hadouken_Recover>();
			Setup<CREATOR_Fighter_0_Jump_Prep_Vertical>();
			Setup<CREATOR_Fighter_0_Jump_Prep_Forward>();
			Setup<CREATOR_Fighter_0_Jump_Prep_Back>();
			Setup<CREATOR_Fighter_0_Jump_Up_Vertical>();
			Setup<CREATOR_Fighter_0_Jump_Up_Forward>();
			Setup<CREATOR_Fighter_0_Jump_Up_Back>();

			Load<Fighter_0_Crouch>();
			//Load<Fighter_0_Hadouken_Fire>();
			//Load<Fighter_0_Hadouken_Recover>();
			//Load<Fighter_0_HitReaction_Side>();
			//Load<Fighter_0_HitReaction_Up>();
			//Load<Fighter_0_Idle>();
			//Load<Fighter_0_Jab>();
			Load<Fighter_0_Jump_Fall>();
			//Load<Fighter_0_Jump_Prep_Back>();
			//Load<Fighter_0_Jump_Prep_Forward>();
			//Load<Fighter_0_Jump_Prep_Vertical>();
			//Load<Fighter_0_Jump_Up_Back>();
			//Load<Fighter_0_Jump_Up_Forward>();
			//Load<Fighter_0_Jump_Up_Vertical>();
			Load<Fighter_0_Jump_WeakPunch>();
			//Load<Fighter_0_WalkBack>();
			//Load<Fighter_0_WalkForward>();
			Load<Fighter_0_Uppercut>();
		}
	};
}