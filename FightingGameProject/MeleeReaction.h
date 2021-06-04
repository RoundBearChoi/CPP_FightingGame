#pragma once
#include <vector>
#include "GameObj.h"
#include "CollisionResult.h"

namespace RB
{
	class MeleeReaction
	{
	private:
		std::vector<GameObj*> _vecFighters;
		ImpactEffectsGroup* _impactEffects = nullptr;

	public:
		MeleeReaction(GameObj* fighter0, GameObj* fighter1, ImpactEffectsGroup* impactEffectsGroup)
		{
			_vecFighters.push_back(fighter0);
			_vecFighters.push_back(fighter1);
			_impactEffects = impactEffectsGroup;
		}

		void Update(int32_t index, CollisionResult collisionResult)
		{
			if (collisionResult.isCollided)
			{
				IF_COUT{ std::cout << "fighter 0 hits fighter 1!" << std::endl; };

				_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, collisionResult.midPoint);

				if (collisionResult.damageData.upPush != 0)
				{
					_vecFighters[index]->AddJump(collisionResult.damageData.upPush, collisionResult.damageData.sidePush);
					_vecFighters[index]->SetNextState(State::NewState<Fighter_0_HitReaction_Up>(&_vecFighters[index]->objData));
				}
				else
				{
					_vecFighters[index]->SetNextState(State::NewState<Fighter_0_HitReaction_Side>(&_vecFighters[index]->objData));
				}
			}
		}
	};
}