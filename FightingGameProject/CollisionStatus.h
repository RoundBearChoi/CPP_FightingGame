#pragma once
#include "BodyType.h"

namespace RB
{
	class CollisionStatus
	{
	public:
		std::vector<BodyType> vecBodies;
		int32_t frame = 0;
		bool processed = false;
	};
}