#pragma once
#include "State.h"

namespace RB
{
	class Fighter_1_Idle : public State
	{
	public:
		GET_HASH_OVERRIDE;

		Fighter_1_Idle()
		{
			animationController.SetSpritePath("PNG files/Fighter_1/fighter_1_idle.png");

			animationController.SetParams(SpriteType::FIGHTER_1, 0, 1080, 180, 6, 1, 6);
			animationController.status.nTransitionDelay = 12;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 180, 180 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}