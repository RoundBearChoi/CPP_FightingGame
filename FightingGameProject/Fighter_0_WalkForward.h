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
			animationController.SetParams(SpriteType::NONE, (int32_t)FighterSpriteType::fighter_0_walk, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 8;
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			if (objData.GetTransitionPermission())
			{
				if (!gameData.key_d)
				{
					nextState = State::NewState<Fighter_0_Idle>();
				}
			}
		}
	};
}