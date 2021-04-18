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
#include "Fighter_0_Jump_Up_Vertical.h"
#include "Fighter_0_Jump_Up_Forward.h"
#include "Fighter_0_Jump_Fall.h"

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
			Load<Fighter_0_Idle>();
			Load<Fighter_0_WalkForward>();
			Load<Fighter_0_WalkBack>();
			Load<Fighter_0_Jab>();
			Load<Fighter_0_HitReaction_0>();
			Load<Fighter_0_Hadouken_Fire>();
			Load<Fighter_0_Hadouken_Recover>();
		}
	};
}