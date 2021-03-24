#include "Camera.h"

namespace RB
{
	void Camera::Update(GameData& gameData)
	{
		if (gameData.key_j && gameData.key_l || !gameData.key_j && !gameData.key_l)
		{
			// double press (do nothing)
		}
		else if (gameData.key_j)
		{
			position.x -= 4;
		}
		else if (gameData.key_l)
		{
			position.x += 4;
		}

		if (gameData.key_i && gameData.key_k || !gameData.key_i && !gameData.key_k)
		{
			// double press (do nothing)
		}
		else if (gameData.key_i)
		{
			zoomScale += 0.005f;
		}
		else if (gameData.key_k)
		{
			zoomScale -= 0.005f;
		}

		float y = -(float)GameSettings::window_height * 0.4f / zoomScale;
		position.y = (int32_t)std::round(y);
	}
}