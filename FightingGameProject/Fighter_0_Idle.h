#pragma once
#include "State.h"

namespace RB
{
	class Fighter_0_WalkForward;
	class Fighter_0_Jab;

	class Fighter_0_Idle : public State
	{
	public:
		STATIC_VEC_COLLIDERS;
		STATIC_VEC_COLLIDER_QUADS;

		Fighter_0_Idle()
		{
			animationController.SetSpritePath("PNG files/Fighter_0/fighter_0_idle.png");

			animationController.SetParams(SpriteType::FIGHTER_0, 0, 2000, 200, 5, 1, 5);
			animationController.status.nTransitionDelay = 10;
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
			UpdateColliders(GetColliders(), GetColliderQuads());

			if (objData.GetTransitionPermission())
			{
				if (gameData.key_t)
				{
					gameData.key_t->processed = true;
					nextState = State::NewState<Fighter_0_Jab>();
				}

				if (gameData.key_d)
				{
					nextState = State::NewState<Fighter_0_WalkForward>();
				}
			}
		}
	};
}