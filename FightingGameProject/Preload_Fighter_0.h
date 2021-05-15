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

			sampleStates.push_back(State::NewState<Fighter_0_Idle>());
			sampleStates.push_back(State::NewState<Fighter_0_WalkForward>());
			sampleStates.push_back(State::NewState<Fighter_0_WalkBack>());
			sampleStates.push_back(State::NewState<Fighter_0_Jab>());
			sampleStates.push_back(State::NewState<Fighter_0_HitReaction_Side>());
			sampleStates.push_back(State::NewState<Fighter_0_HitReaction_Up>());
			sampleStates.push_back(State::NewState<Fighter_0_Hadouken_Fire>());
			sampleStates.push_back(State::NewState<Fighter_0_Hadouken_Recover>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Prep_Vertical>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Prep_Forward>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Prep_Back>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Up_Vertical>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Up_Forward>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Up_Back>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_Fall>());
			sampleStates.push_back(State::NewState<Fighter_0_Jump_WeakPunch>());
			sampleStates.push_back(State::NewState<Fighter_0_Crouch>());
			sampleStates.push_back(State::NewState<Fighter_0_Uppercut>());

			for (size_t i = 0; i < sampleStates.size(); i++)
			{
				sampleStates[i]->UpdateColliderParts();
				delete sampleStates[i];
			}
		}
	};
}