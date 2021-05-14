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

			sampleStates.push_back(stateFactory->Creator_Fighter_0_Idle->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_WalkForward->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_WalkBack->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jab->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_HitReactionSide->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_HitReactionUp->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Hadouken_Fire->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Hadouken_Recover->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Prep_Vertical->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Prep_Forward->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Prep_Back->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Up_Vertical->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Up_Forward->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Up_Back->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_Fall->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Jump_WeakPunch->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Crouch->Create());
			sampleStates.push_back(stateFactory->Creator_Fighter_0_Uppercut->Create());

			for (size_t i = 0; i < sampleStates.size(); i++)
			{
				sampleStates[i]->UpdateColliderParts();
				delete sampleStates[i];
			}
		}
	};
}