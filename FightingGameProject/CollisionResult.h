#pragma once
#include "olcPixelGameEngine.h"
#include "DamageData.h"

namespace RB
{
	class CollisionResult
	{
	public:
		bool isCollided = false;
		olc::vi2d midPoint = { 0, 0 };
		DamageData damageData;
	};
}