#pragma once
#include <stdint.h>
#include "olcPixelGameEngine.h"

namespace RB
{
	class BoxCollider
	{
	private:
		olc::vi2d pos = { 0, 0 };
		int32_t width = 0;
		int32_t height = 0;
		float rotation = 0.0f;

		std::array<olc::vi2d, 4> quad;
		std::array<olc::vi2d, 4> rotatedQuad;

	public:
		BoxCollider()
		{

		}

		olc::vi2d TopLeft() { return rotatedQuad[0]; }
		olc::vi2d BottomLeft() { return rotatedQuad[1]; }
		olc::vi2d BottomRight() { return rotatedQuad[2]; }
		olc::vi2d TopRight() { return rotatedQuad[3]; }

		BoxCollider(olc::vi2d _pos, int32_t _width, int32_t _height, float _rotation)
		{
			pos = _pos;
			width = _width;
			height = _height;
			rotation = _rotation;

			int32_t topLeftX = (int32_t)std::round((float)pos.x - (float)width / 2.0f);
			int32_t topLeftY = (int32_t)std::round((float)pos.y - (float)height / 2.0f);
			olc::vi2d topLeft = { topLeftX, topLeftY };
			olc::vi2d bottomLeft = topLeft + olc::vi2d{ 0, height };
			olc::vi2d topRight = topLeft + olc::vi2d{ width, 0 };
			olc::vi2d bottomRight = topLeft + olc::vi2d{ width, height };

			quad[0] = topLeft;
			quad[1] = bottomLeft;
			quad[2] = bottomRight;
			quad[3] = topRight;
		}

		void UpdateRotation(float angle)
		{
			for (int i = 0; i < quad.size(); i++)
			{
				float fX = ((float)quad[i].x * cosf(angle)) - ((float)quad[i].y * sinf(angle)) + (float)pos.x;
				float fY = ((float)quad[i].x * sinf(angle)) + ((float)quad[i].y * cosf(angle)) + (float)pos.y;

				rotatedQuad[i] = { (int32_t)std::round(fX), (int32_t)std::round(fY) };
			}

			//for (auto& r : vecShapes)
			//{
			//	for (int i = 0; i < r.o.size(); i++)
			//		r.p[i] =
			//	{	// 2D Rotation Transform + 2D Translation
			//		(r.o[i].x * cosf(r.angle)) - (r.o[i].y * sinf(r.angle)) + r.pos.x,
			//		(r.o[i].x * sinf(r.angle)) + (r.o[i].y * cosf(r.angle)) + r.pos.y,
			//	};
			//
			//	r.overlap = false;
			//}
		}
	};
}