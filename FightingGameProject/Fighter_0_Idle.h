#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Fighter_0_WalkForward;
	class Fighter_0_Jab;

	class Fighter_0_Idle : public State
	{
	public:
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_0_idle, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 10;
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			if (gameData.t != nullptr)
			{
				gameData.t->processed = true;
				nextState = State::NewState<Fighter_0_Jab>();
			}

			if (gameData.d)
			{
				nextState = State::NewState<Fighter_0_WalkForward>();
			}
		}
	};
}