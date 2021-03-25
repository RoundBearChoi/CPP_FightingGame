#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class CollisionCheck
	{
	public:
		std::vector<olc::vi2d> quads;
		int32_t frame = 0;
	};
}