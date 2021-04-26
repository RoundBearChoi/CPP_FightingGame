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

		}
	};
}