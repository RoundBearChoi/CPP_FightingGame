#pragma once
#include "olcPixelGameEngine.h"
#include "GameWindow.h"

namespace RB
{
	class Camera
	{
	private:
		olc::vf2d position{ 0.0f, 0.0f };
		float scale = 1.0f;

	public:
		Camera()
		{
			position.x = (float)GameWindow::GetWidth() * 0.5f;
			position.y = (float)GameWindow::GetHeight() * 0.9f;
		}

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