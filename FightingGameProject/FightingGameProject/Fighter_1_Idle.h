#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Fighter_1_Idle : public State
	{
	public:
		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams((int32_t)FighterSpriteType::fighter_1_idle, 1080, 180, 6, 1, 6);
			animationController.status.nTransitionDelay = 12;
			objData.SetSpriteSize({ 180, 180 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}