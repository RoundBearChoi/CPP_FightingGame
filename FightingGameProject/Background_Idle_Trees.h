#pragma once
#include "State.h"

namespace RB
{
	class Background_Idle_Trees : public State
	{
	public:
		Background_Idle_Trees()
		{
			animationController.SetSpritePath("PNG files/Background/background_trees_20.png");
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams(SpriteType::BACKGROUND, 1700, 300, 1, 1, 1);
			objData.SetSpriteSize({ 1700, 300 });
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