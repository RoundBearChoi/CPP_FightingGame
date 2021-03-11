#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Background_Idle_Trees : public State
	{
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::background_trees, 854, 480, 1, 1, 1);
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}