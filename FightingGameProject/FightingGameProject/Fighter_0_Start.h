#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Start : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_0_idle, 900, 180, 5, 1, 5);
			//animationController.status.nTransitionDelay = 2;
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			//olc::vi2d pos = objData.GetPosition();
			//pos.x -= 1;
			//objData.SetPosition(pos);
		}
	};
}