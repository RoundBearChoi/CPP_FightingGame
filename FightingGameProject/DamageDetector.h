#pragma once

namespace RB
{
	class DamageDetector
	{
	private:
		ObjGroup* fighters = nullptr;
		ObjGroup* projectiles = nullptr;

	public:
		DamageDetector(ObjGroup* _fighters, ObjGroup* _projectiles)
		{
			fighters = _fighters;
			projectiles = _projectiles;
		}
	};
}