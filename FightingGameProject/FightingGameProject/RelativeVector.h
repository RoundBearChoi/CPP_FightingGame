#pragma once
#include "olcPixelGameEngine.h"
#include "GameWindow.h"

namespace RB
{
	class RelativeVector
	{
	public:
		static olc::vi2d Get(const olc::vi2d& objPos, const olc::vi2d& camPos, const float& scale)
		{
			olc::vi2d fromCam = objPos - camPos;

			float x = (float)fromCam.x * scale;
			float y = (float)fromCam.y * scale;

			fromCam = { (int32_t)std::round(x), (int32_t)std::round(y) };

			olc::vi2d screenCenter{ GameWindow::GetWidth() / 2, GameWindow::GetHeight() / 2 };
			olc::vi2d screenPos = screenCenter + fromCam;

			return screenPos;
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