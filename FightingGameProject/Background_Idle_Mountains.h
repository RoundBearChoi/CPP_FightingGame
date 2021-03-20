#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Background_Idle_Mountains : public State
	{
	public:
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams(SpriteType::BACKGROUND, (int32_t)FighterSpriteType::background_mountains, 1700, 300, 1, 1, 1);
			objData.SetSpriteSize({ 1700, 300 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}