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

		std::array<olc::vi2d, 4> relativePoints;

	public:
		BoxCollider()
		{

		}

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

			relativePoints[0] = topLeft;
			relativePoints[1] = bottomLeft;
			relativePoints[2] = bottomRight;
			relativePoints[3] = topRight;
		}

		void UpdateRotation()
		{

		}
	};
}