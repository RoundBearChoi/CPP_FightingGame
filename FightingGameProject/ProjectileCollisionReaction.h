#pragma once
#include <stdint.h>
#include <vector>
#include "PlayerToProjectileCollisionResult.h"
#include "GameObj.h"

//hitstop messages
#include "FightersHitStopMessage.h"
#include "ProjectilesHitStopMessage.h"

namespace RB
{
	class ProjectileCollisionReaction
	{
	private:
		ObjGroup* _fighters = nullptr;
		ObjGroup* _projectiles = nullptr;
		ObjGroup* _impactEffects = nullptr;

	public:
		ProjectileCollisionReaction(ObjGroup* fighters, ObjGroup* projectiles, ObjGroup* impactEffects)
		{
			_fighters = fighters;
			_projectiles = projectiles;
			_impactEffects = impactEffects;
		}

		void Update(int32_t fighterIndex, PlayerToProjectileCollisionResult collisionResult)
		{
			if (collisionResult.isCollided)
			{
				//midair hits
				if (_fighters->GetObj(fighterIndex)->objData.GetPosition().y < 0)
				{
					_projectiles->DeleteObj(collisionResult.projectileIndex);
					_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, collisionResult.midPoint);

					JumpSpecs jumpSpecs(10, 2, 1, true, true, false);

					_fighters->GetObj(fighterIndex)->objData.CreateNewJumpCalculator();
					_fighters->GetObj(fighterIndex)->objData.ptrJumpCalculator->SetSpecs(jumpSpecs);
					_fighters->GetObj(fighterIndex)->SetNextState(State::NewState<Fighter_0_HitReaction_Up>(_fighters->GetObjData(fighterIndex)));

					FightersHitStopMessage fightersHitStop;
					ProjectilesHitStopMessage projectilesHitStop;
					fightersHitStop.Register(12);
					projectilesHitStop.Register(12);
				}
				//ground hits
				else
				{
					_projectiles->DeleteObj(collisionResult.projectileIndex);
					_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, collisionResult.midPoint);

					_fighters->GetObj(fighterIndex)->SetNextState(State::NewState<Fighter_0_HitReaction_Side>(_fighters->GetObjData(fighterIndex)));
					
					FightersHitStopMessage fightersHitStop;
					ProjectilesHitStopMessage projectilesHitStop;
					fightersHitStop.Register(12);
					projectilesHitStop.Register(12);
				}
			}
		}
	};
}