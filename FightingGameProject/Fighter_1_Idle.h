#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Fighter_1_Idle : public State
	{
	public:
		Fighter_1_Idle()
		{
			animationController.SetParams(SpriteType::NONE, (int32_t)FighterSpriteType::fighter_1_idle, 1080, 180, 6, 1, 6);
			animationController.status.nTransitionDelay = 12;
		}

		size_t GetHash() override
		{
			static size_t hash = 0;
			MakeHash(hash);

			return hash;
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