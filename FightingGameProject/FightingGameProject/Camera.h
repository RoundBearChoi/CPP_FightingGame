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
			position.x = -(float)GameWindow::GetWidth() / 2.0f;
			position.y = -(float)GameWindow::GetHeight() / 2.0f;
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