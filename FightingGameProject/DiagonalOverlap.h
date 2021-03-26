#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class DiagonalOverlap
	{
	public:
		static bool yes(olc::vi2d& p1Pos, std::array<olc::vi2d, 4>& p1Quads, olc::vi2d& p2Pos, std::array<olc::vi2d, 4>& p2Quads)
		{
			olc::vi2d* r1 = &p1Pos;
			std::array<olc::vi2d, 4>* r1Quads = &p1Quads;

			olc::vi2d* r2 = &p2Pos;
			std::array<olc::vi2d, 4>* r2Quads = &p2Quads;

			for (int32_t shape = 0; shape < 2; shape++)
			{
				//switch
				if (shape == 1)
				{
					r1 = &p2Pos;
					r1Quads = &p2Quads;

					r2 = &p1Pos;
					r2Quads = &p1Quads;
				}

				// Check diagonals of polygon...
				for (int32_t p = 0; p < r1Quads->size(); p++)
				{
					olc::vi2d line_r1s = *r1;
					olc::vi2d line_r1e = (*r1Quads)[p];

					// ...against edges of the other
					for (int32_t q = 0; q < r2Quads->size(); q++)
					{
						olc::vi2d line_r2s = (*r2Quads)[q];
						olc::vi2d line_r2e = (*r2Quads)[(q + 1) % r2Quads->size()];

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
			}

			return false;
		}
	};
}