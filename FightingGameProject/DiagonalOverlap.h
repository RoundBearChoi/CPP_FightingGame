#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class DiagonalOverlap
	{
	public:
		static bool yes(olc::vi2d& p1Pos, std::array<olc::vi2d, 4>& p1Quads, std::array<olc::vi2d, 4>& p2Quads)
		{
			//polygon* poly1 = &r1;
			//polygon* poly2 = &r2;

			//for (int32_t shape = 0; shape < 2; shape++)
			//{
				//if (shape == 1)
				//{
				//	poly1 = &r2;
				//	poly2 = &r1;
				//}

				// Check diagonals of polygon...
				for (int32_t p = 0; p < p1Quads.size(); p++)
				{
					olc::vi2d line_r1s = p1Pos;
					olc::vi2d line_r1e = p1Quads[p];

					// ...against edges of the other
					for (int32_t q = 0; q < p2Quads.size(); q++)
					{
						olc::vi2d line_r2s = p2Quads[q];
						olc::vi2d line_r2e = p2Quads[(q + 1) % p2Quads.size()];

						// Standard "off the shelf" line segment intersection
						float h = (float)(line_r2e.x - line_r2s.x) * (float)(line_r1s.y - line_r1e.y) - (float)(line_r1s.x - line_r1e.x) * (float)(line_r2e.y - line_r2s.y);
						float t1 = ((float)(line_r2s.y - line_r2e.y) * (float)(line_r1s.x - line_r2s.x) + (float)(line_r2e.x - line_r2s.x) * (float)(line_r1s.y - line_r2s.y)) / h;
						float t2 = ((float)(line_r1s.y - line_r1e.y) * (float)(line_r1s.x - line_r2s.x) + (float)(line_r1e.x - line_r1s.x) * (float)(line_r1s.y - line_r2s.y)) / h;

						if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
						{
							return true;
						}
					}
				}
			//}
			return false;
		}
	};
}