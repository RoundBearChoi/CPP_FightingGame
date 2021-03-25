#pragma once
#include "BodyType.h"

namespace RB
{
	class CollisionCheck
	{
	public:
		std::vector<BodyType> vecBodies;
		int32_t frame = 0;
		bool processed = false;
	};
}