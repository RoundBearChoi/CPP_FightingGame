#include "Camera.h"

namespace RB
{
	void Camera::Update(GameData& gameData)
	{
		if (gameData.key_left && gameData.key_right || !gameData.key_left && !gameData.key_right)
		{
			// double press (do nothing)
		}
		else if (gameData.key_left)
		{
			position.x -= 4;
		}
		else if (gameData.key_right)
		{
			position.x += 4;
		}

		if (gameData.key_up && gameData.key_down || !gameData.key_up && !gameData.key_down)
		{
			// double press (do nothing)
		}
		else if (gameData.key_up)
		{
			zoomScale += 0.005f;
		}
		else if (gameData.key_down)
		{
			zoomScale -= 0.005f;
		}

		float y = -(float)GameSettings::window_height * 0.4f / zoomScale;
		position.y = (int32_t)std::round(y);
	}
}