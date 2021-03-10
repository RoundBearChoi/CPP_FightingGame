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
		void Update(GameData& gameData)
		{
			if (gameData.left && gameData.right || !gameData.left && !gameData.right)
			{
				// double press (do nothing)
			}
			else if (gameData.left)
			{
				position.x -= 4;
			}
			else if (gameData.right)
			{
				position.x += 4;
			}

			if (gameData.up && gameData.down || !gameData.up && !gameData.down)
			{
				// double press (do nothing)
			}
			else if (gameData.up)
			{
				zoomScale += 0.005f;
			}
			else if (gameData.down)
			{
				zoomScale -= 0.005f;
			}

			float y = -(float)WINDOW_HEIGHT * 0.35f / zoomScale;
			position.y = (int32_t)std::round(y);
		}

		olc::vi2d GetPosition() { return position; }
		float GetZoom() { return zoomScale; }
	};
}