#pragma once
#include "olcPixelGameEngine.h"
#include "DamageData.h"
#include "GameObj.h"

namespace RB
{
	class MeleeCollisionResult
	{
	public:
		bool isCollided = false;
		olc::vi2d midPoint = { 0, 0 };
		DamageData damageData;
	};
}