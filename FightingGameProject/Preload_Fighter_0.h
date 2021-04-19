#pragma once
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_HitReaction_0.h"
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

	public:
		Preload_Fighter_0()
		{
			Load<Fighter_0_Crouch>();
			Load<Fighter_0_Hadouken_Fire>();
			Load<Fighter_0_Hadouken_Recover>();
			Load<Fighter_0_HitReaction_0>();
			Load<Fighter_0_Idle>();
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
		}
	};
}