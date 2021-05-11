#pragma once
//#include "Fighter_0_Idle.h"
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
#include "Fighter_0_Crouch.h"
#include "Fighter_0_Uppercut.h"

#include "StateFactory.h"
#include "ConcreteStateCreators.h"

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
		void Setup()
		{
			T* creator = new T();
			State* newState = creator->Create();
			newState->UpdateColliderParts();
			delete newState;

			StateFactory::ptr->Creator_Fighter_0_Idle = creator;
		}

	public:
		Preload_Fighter_0()
		{
			Setup<Fighter_0_Idle_Creator>();

			Load<Fighter_0_Crouch>();
			Load<Fighter_0_Hadouken_Fire>();
			Load<Fighter_0_Hadouken_Recover>();
			Load<Fighter_0_HitReaction_Side>();
			Load<Fighter_0_HitReaction_Up>();
			//Load<Fighter_0_Idle>();
			Load<Fighter_0_Jab>();
			Load<Fighter_0_Jump_Fall>();
			Load<Fighter_0_Jump_Prep_Back>();
			Load<Fighter_0_Jump_Prep_Forward>();
			Load<Fighter_0_Jump_Prep_Vertical>();
			Load<Fighter_0_Jump_Up_Back>();
			Load<Fighter_0_Jump_Up_Forward>();
			Load<Fighter_0_Jump_Up_Vertical>();
			Load<Fighter_0_Jump_WeakPunch>();
			Load<Fighter_0_WalkBack>();
			Load<Fighter_0_WalkForward>();
			Load<Fighter_0_Uppercut>();
		}
	};
}