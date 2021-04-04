#pragma once
#include "ProjectileType.h"
#include "olcPixelGameEngine.h"

namespace RB
{
	class CreateProjectile
	{
	public:
		ProjectileType projectileType = ProjectileType::NONE;
		olc::vi2d forward = { 0, 0 };
		olc::vi2d startPos = { 0, 0 };
		size_t ownerObjCreationID = 0;
	};
}