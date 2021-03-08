#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class Camera
	{
	private:
		olc::vf2d position{ 0.0f, 0.0f };
		float scale = 1.0f;

	public:
		olc::vf2d GetPosition()
		{
			return position;
		}

		float GetScale()
		{
			return scale;
		}
	};
}