#pragma once

namespace RB
{
	class DamageDetector
	{
	private:
		ObjGroup* _fighters = nullptr;
		ObjGroup* _projectiles = nullptr;
		ObjGroup* _impactEffects = nullptr;

	public:
		DamageDetector(ObjGroup* fighters, ObjGroup* projectiles, ObjGroup* impactEffects)
		{
			_fighters = fighters;
			_projectiles = projectiles;
			_impactEffects = impactEffects;
		}

		void Update()
		{
			for (int32_t i = 0; i < 2; i++)
			{
				//projectiles vs player collision
				size_t resultProjectile = 0;
				olc::vi2d resultMidPoint;

				if (ProjectileCollision::IsColliding(i, *_fighters, *_projectiles, resultProjectile, resultMidPoint))
				{
					_projectiles->DeleteObj(resultProjectile);
					_fighters->SetNextState(i, State::NewState<Fighter_0_HitReaction_Side>(_fighters->GetObjData(i)));
					_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, resultMidPoint);

					SlowMotionMessage slow;
					slow.interval = 15;
					slow.maxCount = 1;
					_fighters->vecSlowMotion.push_back(slow);
				}

				//body part vs body part collision
				olc::vi2d resultCollision;
				DamageData resultDamage;
				int32_t enemy = 0;

				if (i == 0)
				{
					enemy = 1;
				}

				if (BodyPartCollision::IsColliding(enemy, *_fighters, resultCollision, resultDamage))
				{
					_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, resultCollision);

					if (resultDamage.upPush != 0)
					{
						_fighters->jumpAdder->AddJump(i, resultDamage.upPush, resultDamage.sidePush);
						_fighters->SetNextState(i, State::NewState<Fighter_0_HitReaction_Up>(_fighters->GetObjData(i)));
					}
					else
					{
						_fighters->SetNextState(i, State::NewState<Fighter_0_HitReaction_Side>(_fighters->GetObjData(i)));
					}

					SlowMotionMessage slow;
					slow.interval = 15;
					slow.maxCount = 1;
					_fighters->vecSlowMotion.push_back(slow);
				}
			}
		}
	};
}