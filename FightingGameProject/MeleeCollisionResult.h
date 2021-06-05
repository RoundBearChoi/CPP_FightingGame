#pragma once
#include "olcPixelGameEngine.h"
#include "DamageData.h"

namespace RB
{
	class MeleeCollisionResult
	{
	public:
		bool isCollided = false;
		olc::vi2d midPoint = { 0, 0 };
		DamageData damageData;
		int32_t attackerIndex = 0;
	};
}