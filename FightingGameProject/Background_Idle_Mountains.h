#pragma once
#include "State.h"

namespace RB
{
	class Background_Idle_Mountains : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Background_Idle_Mountains()
		{
			animationController.SetSpritePath("PNG files/Background/background_mountains.png");
			animationController.SetParams(SpriteType::BACKGROUND, 1700, 300, 1, 1, 1);
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 1700, 300 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}