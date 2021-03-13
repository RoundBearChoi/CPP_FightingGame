#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Fighter_0_Start : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_0_idle, 1080, 180, 6, 1, 6);
			animationController.status.nTransitionDelay = 12;
			objData.SetSpriteSize({ 180, 180 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			//olc::vi2d pos = objData.GetPosition();
			//pos.x -= 1;
			//objData.SetPosition(pos);
		}
	};
}