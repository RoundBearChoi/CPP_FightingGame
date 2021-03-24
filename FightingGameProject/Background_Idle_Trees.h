#pragma once
#include "State.h"

namespace RB
{
	class Background_Idle_Trees : public State
	{
	public:
		GET_HASH_OVERRIDE;

		Background_Idle_Trees()
		{
			animationController.SetSpritePath("PNG files/Background/background_trees_20.png");
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams(SpriteType::BACKGROUND, 0 /*no need*/, 1700, 300, 1, 1, 1);
			objData.SetSpriteSize({ 1700, 300 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}