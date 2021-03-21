#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_WalkForward : public State
	{
	public:
		Fighter_0_WalkForward()
		{
			path = "PNG files/Fighter_0/fighter_0_walk.png";

			animationController.SetParams(SpriteType::FIGHTER_0, (int32_t)FighterSpriteType::fighter_0_walk, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 8;
		}

		size_t GetHash() override
		{
			static size_t hash = 0;
			MakeHash(hash);

			return hash;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			if (objData.GetTransitionPermission())
			{
				if (!gameData.key_d)
				{
					nextState = State::NewState<Fighter_0_Idle>();
				}
			}
		}
	};
}