#pragma once
#include "State.h"

namespace RB
{
	class Fighter_1_Start : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_1_idle, 900, 180, 5, 1, 5);
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}