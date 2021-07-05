#pragma once
#include <vector>
#include "GameObj.h"
#include "MeleeCollisionResult.h"

//hitstop messages
#include "FightersHitStopMessage.h"
#include "ProjectilesHitStopMessage.h"

namespace RB
{
	class MeleeReaction
	{
	private:
		std::vector<ObjBase*> _vecFighters;
		ImpactEffectsGroup* _impactEffects = nullptr;

	public:
		MeleeReaction(ObjBase* fighter0, ObjBase* fighter1, ImpactEffectsGroup* impactEffectsGroup)
		{
			_vecFighters.push_back(fighter0);
			_vecFighters.push_back(fighter1);
			_impactEffects = impactEffectsGroup;
		}

		void Update(int32_t index, MeleeCollisionResult collisionResult)
		{
			if (collisionResult.isCollided)
			{
				IF_COUT{ std::cout << "fighter 0 hits fighter 1!" << std::endl; };

				_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, collisionResult.midPoint);

				//midair hits
				if (_vecFighters[index]->objData.GetPosition().y < 0)
				{
					JumpSpecs jumpSpecs(10, 2, 1, true, true, false);

					_vecFighters[index]->objData.CreateNewJumpCalculator();
					_vecFighters[index]->objData.ptrJumpCalculator->SetSpecs(jumpSpecs);
					_vecFighters[index]->SetNextState(State::NewState<Fighter_0_HitReaction_Up>(_vecFighters[index]));

					FightersHitStopMessage fightersHitStop;
					ProjectilesHitStopMessage projectilesHitStop;
					fightersHitStop.Register(12);
					projectilesHitStop.Register(12);
				}
				//uppercuts from ground
				else if (collisionResult.damageData.upPush > 0)
				{
					JumpSpecs jumpSpecs(collisionResult.damageData.upPush, collisionResult.damageData.sidePush, 1, true, true, false);

					_vecFighters[index]->objData.CreateNewJumpCalculator();
					_vecFighters[index]->objData.ptrJumpCalculator->SetSpecs(jumpSpecs);
					_vecFighters[index]->SetNextState(State::NewState<Fighter_0_HitReaction_Up>(_vecFighters[index]));

					FightersHitStopMessage fightersHitStop;
					ProjectilesHitStopMessage projectilesHitStop;
					fightersHitStop.Register(12);
					projectilesHitStop.Register(12);
				}
				//straight punches&kicks from ground
				else
				{
					_vecFighters[index]->SetNextState(State::NewState<Fighter_0_HitReaction_Side>(_vecFighters[index]));

					FightersHitStopMessage fightersHitStop;
					ProjectilesHitStopMessage projectilesHitStop;
					fightersHitStop.Register(12);
					projectilesHitStop.Register(12);
				}
			}
		}
	};
}