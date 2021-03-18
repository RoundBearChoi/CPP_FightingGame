#pragma once
#include "olcPixelGameEngine.h"
#include "GameSettings.h"
#include "Camera.h"

namespace RB
{
	class RelativeVector
	{
	public:
		static olc::vi2d GetPosition(const olc::vi2d& objPos, Camera& cam)
		{
			olc::vi2d fromCam = objPos - cam.GetPosition();

			float x = (float)fromCam.x * cam.GetZoom();
			float y = (float)fromCam.y * cam.GetZoom();

			fromCam = { (int32_t)std::round(x), (int32_t)std::round(y) };

			olc::vi2d screenCenter{ GameSettings::window_width / 2, GameSettings::window_height / 2 };
			olc::vi2d screenPos = screenCenter + fromCam;

			return screenPos;
		}

		static olc::vi2d GetScale(const olc::vi2d& vector, const float& scale)
		{
			float x = (float)vector.x * scale;
			int32_t roundedX = (int32_t)std::round(x);

			float y = (float)vector.y * scale;
			int32_t roundedY = (int32_t)std::round(y);

			return { roundedX, roundedY };
		}
	};
}