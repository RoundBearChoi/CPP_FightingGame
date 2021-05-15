#pragma once

#include "Fighter_0_Idle.h"
#include "Fighter_0_Idle.h"
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

namespace RB
{
	class Preload_Fighter_0
	{
	public:
		Preload_Fighter_0()
		{
			std::vector<State*> sampleStates;

			sampleStates.push_back(State::NewState<Fighter_0_Idle>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_WalkForward>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_WalkBack>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jab>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_HitReaction_Side>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_HitReaction_Up>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Hadouken_Fire>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Hadouken_Recover>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Prep_Vertical>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Prep_Forward>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Prep_Back>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Up_Vertical>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Up_Forward>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Up_Back>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Fall>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Jump_WeakPunch>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Crouch>(nullptr, nullptr));
			sampleStates.push_back(State::NewState<Fighter_0_Uppercut>(nullptr, nullptr));

			for (size_t i = 0; i < sampleStates.size(); i++)
			{
				sampleStates[i]->UpdateColliderParts();
				delete sampleStates[i];
			}
		}
	};
}