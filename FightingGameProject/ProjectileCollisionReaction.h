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
				_projectiles->DeleteObj(collisionResult.projectileIndex);
				_fighters->GetObj(fighterIndex)->SetNextState(State::NewState<Fighter_0_HitReaction_Side>(_fighters->GetObjData(fighterIndex)));
				_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, collisionResult.midPoint);

				FightersHitStopMessage fightersHitStop;
				ProjectilesHitStopMessage projectilesHitStop;
				fightersHitStop.Register(12);
				projectilesHitStop.Register(12);
			}
		}
	};
}