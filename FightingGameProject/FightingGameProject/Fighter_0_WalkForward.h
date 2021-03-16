#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_WalkForward : public State
	{
	public:
		void OnEnter(ObjData& objData, GameData& gameData) override
		{

		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			if (!gameData.d)
			{
				nextState = State::NewState<Fighter_0_Idle>();
			}
		}
	};
}