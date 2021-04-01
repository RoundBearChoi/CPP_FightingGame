#pragma once
#include "Fighter_0_Idle.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_HitReaction_0.h"

namespace RB
{
	class Preload_Fighter_0
	{
	private:
		template<class T>
		void Load()
		{
			T state;
			state.UpdateColliders();
		}

	public:
		Preload_Fighter_0()
		{
			Load<Fighter_0_Idle>();
			Load<Fighter_0_WalkForward>();
			Load<Fighter_0_WalkBack>();
			Load<Fighter_0_Jab>();
			Load<Fighter_0_HitReaction_0>();
		}
	};
}