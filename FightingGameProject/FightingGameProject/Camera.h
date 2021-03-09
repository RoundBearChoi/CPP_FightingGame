#pragma once
#include "olcPixelGameEngine.h"
#include "GameWindow.h"

namespace RB
{
	class Camera
	{
	private:
		olc::vi2d position{ 0, 0 };
		float zoomScale = 1.0f;

	public:
		Camera()
		{
			position.y = -180;
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

			if (gameData.up && gameData.down || !gameData.up && !gameData.down)
			{

			}
			else if (gameData.up)
			{
				zoomScale += 0.005f;
			}
			else if (gameData.down)
			{
				zoomScale -= 0.005f;
			}
		}

		olc::vi2d GetPosition() { return position; }
		float GetZoom() { return zoomScale; }
	};
}