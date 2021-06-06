#include "Camera.h"

namespace RB
{
	Camera::Camera()
	{

	}

	void Camera::Update()
	{
		InputData& inputData = *InputData::ptr;

		if (inputData.key_j && inputData.key_l || !inputData.key_j && !inputData.key_l)
		{
			// double press (do nothing)
		}
		else if (inputData.key_j)
		{
			position.x -= 4;
		}
		else if (inputData.key_l)
		{

			position.x += 4;
		}

		if (inputData.key_i && inputData.key_k || !inputData.key_i && !inputData.key_k)
		{
			// double press (do nothing)
		}
		else if (inputData.key_i)
		{
			zoomScale += 0.005f;
		}
		else if (inputData.key_k)
		{
			zoomScale -= 0.005f;
		}

		float y = -(float)GameSettings::window_height * 0.4f / zoomScale;
		position.y = (int32_t)std::round(y);
	}
}