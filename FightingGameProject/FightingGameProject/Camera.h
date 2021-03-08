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

		void Update(GameData& gameData)
		{
			if (gameData.left && gameData.right || !gameData.left && !gameData.right)
			{

			}
			else if (gameData.left)
			{
				position.x -= 1.0f;
			}
			else if (gameData.right)
			{
				position.x += 1.0f;
			}
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