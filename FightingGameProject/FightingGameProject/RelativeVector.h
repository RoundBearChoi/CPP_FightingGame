#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class RelativeVector
	{
	public:
		static olc::vi2d Get(const olc::vi2d& objPos, const olc::vi2d& camPos, const float& scale)
		{
			float x = (float)objPos.x + (float)camPos.x;
			x *= scale;
			int32_t roundedX = std::round(x);

			float y = (float)objPos.y + (float)camPos.y;
			y *= scale;
			int32_t roundedY = std::round(y);

			return { roundedX, roundedY };
		}

		static olc::vi2d Get(const olc::vi2d& vector, const float& scale)
		{
			float x = (float)vector.x * scale;
			int32_t roundedX = std::round(x);

			float y = (float)vector.y * scale;
			int32_t roundedY = std::round(y);

			return { roundedX, roundedY };
		}
	};
}