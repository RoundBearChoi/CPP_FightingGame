#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class PlayerToProjectileCollisionResult
	{
	public:
		bool isCollided = false;
		size_t projectileIndex = 0;
		olc::vi2d midPoint;
	};
}