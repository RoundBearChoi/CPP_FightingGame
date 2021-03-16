#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Fighter_0_Idle : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_0_idle_0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 10;
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			//olc::vi2d pos = objData.GetPosition();
			//pos.x -= 1;
			//objData.SetPosition(pos);
		}
	};
}