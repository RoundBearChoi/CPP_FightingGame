#pragma once
#include "olcPixelGameEngine.h"
#include "BoxCollider.h"

namespace RB
{
	class AABB
	{
	public:
		static bool IsColliding(BoxCollider& boxCol1, olc::vi2d p1Position, BoxCollider& boxCol2, olc::vi2d p2Position)
		{
			std::array<olc::vi2d, 4> p1Quad;
			p1Quad[0] = boxCol1.RelativePoint0() + p1Position;
			//p1Quad[1] = boxCol1.RelativePoint1() + p1Position;
			//p1Quad[2] = boxCol1.RelativePoint2() + p1Position;
			p1Quad[3] = boxCol1.RelativePoint3() + p1Position;

			std::array<olc::vi2d, 4> p2Quad;
			p2Quad[0] = boxCol2.RelativePoint0() + p2Position;
			//p2Quad[1] = boxCol2.RelativePoint1() + p2Position;
			//p2Quad[2] = boxCol2.RelativePoint2() + p2Position;
			p2Quad[3] = boxCol2.RelativePoint3() + p2Position;

			if (p1Quad[0].x < p2Quad[3].x && //top left vs top right
				p1Quad[3].x > p2Quad[0].x) //top right vs top left
			{
				return true;
			}

			return false;
		}
	};
}