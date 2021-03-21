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
			path = "PNG files/Fighter_0/fighter_0_jab.png";

			animationController.SetCollisionFileName("Fighter_0/Fighter_0_Jab.collider");
			animationController.SetParams(SpriteType::FIGHTER_0, 0, 2400, 200, 6, 1, 6);
			animationController.status.nTransitionDelay = 5;
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
				if (objData.GetAnimationIndex() == 5)
				{
					nextState = State::NewState<Fighter_0_Idle>();
				}
			}
		}
	};
}