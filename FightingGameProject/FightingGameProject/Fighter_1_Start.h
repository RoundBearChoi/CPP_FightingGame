#pragma once
#include "State.h"

namespace RB
{
	class Fighter_1_Start : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_1_idle, 1080, 180, 6, 1, 6);
			animationController.status.nTransitionDelay = 12;
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}