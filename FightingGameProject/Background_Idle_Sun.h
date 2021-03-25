#pragma once
#include "State.h"

namespace RB
{
	class Background_Idle_Sun : public State
	{
	protected:
		size_t& Hash() override { static size_t hash = 0; return hash; }

	public:
		Background_Idle_Sun()
		{
			animationController.SetSpritePath("PNG files/Background/background_sun.png");
			animationController.SetParams(SpriteType::BACKGROUND, 102, 82, 1, 1, 1);
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 102, 82 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}