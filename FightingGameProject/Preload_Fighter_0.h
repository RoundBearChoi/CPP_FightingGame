#pragma once
#include "StateFactory.h"

namespace RB
{
	class Preload_Fighter_0
	{
	private:
		template<class T>
		void Load()
		{
			T* creator = new T();
			State* newState = creator->Create();
			newState->UpdateColliderParts();

			delete newState;
			delete creator;
		}

	public:
		Preload_Fighter_0()
		{
			Load<CREATOR_Fighter_0_Idle>();
			Load<CREATOR_Fighter_0_WalkForward>();
			Load<CREATOR_Fighter_0_WalkBack>();
			Load<CREATOR_Fighter_0_Jab>();
			Load<CREATOR_Fighter_0_HitReactionSide>();
			Load<CREATOR_Fighter_0_HitReactionUp>();
			Load<CREATOR_Fighter_0_Hadouken_Fire>();
			Load<CREATOR_Fighter_0_Hadouken_Recover>();
			Load<CREATOR_Fighter_0_Jump_Prep_Vertical>();
			Load<CREATOR_Fighter_0_Jump_Prep_Forward>();
			Load<CREATOR_Fighter_0_Jump_Prep_Back>();
			Load<CREATOR_Fighter_0_Jump_Up_Vertical>();
			Load<CREATOR_Fighter_0_Jump_Up_Forward>();
			Load<CREATOR_Fighter_0_Jump_Up_Back>();
			Load<CREATOR_Fighter_0_Jump_Fall>();
			Load<CREATOR_Fighter_0_Jump_WeakPunch>();
			Load<CREATOR_Fighter_0_Crouch>();
			Load<CREATOR_Fighter_0_Uppercut>();
		}
	};
}