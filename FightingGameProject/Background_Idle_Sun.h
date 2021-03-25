#pragma once
#include "State.h"

namespace RB
{
	class Background_Idle_Sun : public State
	{
	public:
		Background_Idle_Sun()
		{
			animationController.SetSpritePath("PNG files/Background/background_sun.png");
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams(SpriteType::BACKGROUND, 0 /*no need*/, 102, 82, 1, 1, 1);
			objData.SetSpriteSize({ 102, 82 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}

		size_t GetHash() override
		{
			static size_t hash = 0;
			MakeHash(hash);
			return hash;
		}
	};
}