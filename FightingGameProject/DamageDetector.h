#pragma once

namespace RB
{
	class DamageDetector
	{
	private:
		ObjGroup* fighters = nullptr;
		ObjGroup* projectiles = nullptr;
		ObjGroup* impactEffects = nullptr;

	public:
		DamageDetector(ObjGroup* _fighters, ObjGroup* _projectiles, ObjGroup* _impactEffects)
		{
			fighters = _fighters;
			projectiles = _projectiles;
			impactEffects = _impactEffects;
		}

		void Update()
		{
			for (int32_t i = 0; i < 2; i++)
			{
				//projectiles vs player collision
				size_t resultProjectile = 0;
				olc::vi2d resultMidPoint;

				if (ProjectileCollision::IsColliding(i, *fighters, *projectiles, resultProjectile, resultMidPoint))
				{
					projectiles->DeleteObj(resultProjectile);
					fighters->SetNextState(i, State::NewState<Fighter_0_HitReaction_Side>());
					impactEffects->CreateObj(ObjType::HIT_EFFECT_0, resultMidPoint);
				}

				//body part vs body part collision
				olc::vi2d resultCollision;
				DamageData resultDamage;
				int32_t enemy = 0;

				if (i == 0)
				{
					enemy = 1;
				}

				if (BodyPartCollision::IsColliding(enemy, *fighters, resultCollision, resultDamage))
				{
					impactEffects->CreateObj(ObjType::HIT_EFFECT_0, resultCollision);

					if (resultDamage.upPush != 0)
					{
						fighters->AddJumpProcessor(i, resultDamage.upPush, resultDamage.sidePush);
						fighters->SetNextState(i, State::NewState<Fighter_0_HitReaction_Up>());
					}
					else
					{
						fighters->SetNextState(i, State::NewState<Fighter_0_HitReaction_Side>());
					}
				}
			}
		}
	};
}