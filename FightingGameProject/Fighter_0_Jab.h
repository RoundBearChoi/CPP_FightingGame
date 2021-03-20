#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_Idle;

	class Fighter_0_Jab : public State
	{
	public:
		Fighter_0_Jab()
		{
			animationController.SetCollisionFileName("Fighter_0/Fighter_0_Jab.collider");
			animationController.SetParams((int32_t)FighterSpriteType::fighter_0_jab, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 5;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			objData.SetSpriteSize({ 400, 230 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{
			if (objData.GetTransitionPermission())
			{
				if (objData.GetAnimationIndex() == 5)
				{
					nextState = State::NewState<Fighter_0_Idle>();
				}
			}
		}
	};
}