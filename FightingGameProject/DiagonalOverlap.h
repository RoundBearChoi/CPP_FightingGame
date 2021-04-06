#pragma once
#include "olcPixelGameEngine.h"
#include "GameObj.h"
#include "BodyType.h"

namespace RB
{
	class DiagonalOverlap
	{
	public:
		static bool Overlapping(olc::vi2d& p1Pos, std::array<olc::vi2d, 4>& p1Quads, olc::vi2d& p2Pos, std::array<olc::vi2d, 4>& p2Quads);
	};
}