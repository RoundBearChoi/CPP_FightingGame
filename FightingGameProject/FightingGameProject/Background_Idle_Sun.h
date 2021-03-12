#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Background_Idle_Sun : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::background_sun, 102, 82, 1, 1, 1);
			objData.SetSpriteSize({ 102, 82 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}