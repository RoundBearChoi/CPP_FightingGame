#pragma once
#include "StateFactory.h"

namespace RB
{
	class Preload_Fighter_0
	{
	public:
		Preload_Fighter_0(StateFactory* stateFactory)
		{
			std::vector<State*> sampleStates;

			sampleStates.push_back(stateFactory->Creator_Fighter_0_Idle->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_WalkForward->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_WalkBack->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jab->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_HitReactionSide->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_HitReactionUp->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Hadouken_Fire->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Hadouken_Recover->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Prep_Vertical->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Prep_Forward->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Prep_Back->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Up_Vertical->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Up_Forward->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Up_Back->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Fall->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_WeakPunch->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Crouch->Create(nullptr, nullptr));
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Uppercut->Create(nullptr, nullptr));

			for (size_t i = 0; i < sampleStates.size(); i++)
			{
				sampleStates[i]->UpdateColliderParts();
				delete sampleStates[i];
			}
		}
	};
}