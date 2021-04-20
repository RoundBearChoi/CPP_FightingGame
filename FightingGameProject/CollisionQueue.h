#pragma once
#include "BodyType.h"
#include "DamageData.h"

namespace RB
{
	class CollisionQueue
	{
	public:
		std::vector<BodyType> vecBodies;
		int32_t animationTile = 0;
		DamageData damageData;
	};
}