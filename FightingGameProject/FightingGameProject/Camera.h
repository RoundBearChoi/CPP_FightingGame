#pragma once
#include "olcPixelGameEngine.h"
#include "GameWindow.h"

namespace RB
{
	class Camera
	{
	private:
		olc::vi2d position{ 0, 0 };
		float scale = 1.0f;

	public:
		Camera()
		{
			position.x = GameWindow::GetWidth() / 2;
			position.y = GameWindow::GetHeight() - 50;
		}

		void Update(GameData& gameData)
		{
			if (gameData.left && gameData.right || !gameData.left && !gameData.right)
			{

			}
			else if (gameData.left)
			{
				position.x -= 1;
			}
			else if (gameData.right)
			{
				position.x += 1;
			}
		}

		olc::vi2d GetPosition()
		{
			return position;
		}

		float GetScale()
		{
			return scale;
		}
	};
}