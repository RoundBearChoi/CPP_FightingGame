#pragma once
#include "olcPixelGameEngine.h"
#include "GameSettings.h"
#include "InputData.h"

namespace RB
{
	class Camera
	{
	private:
		olc::vi2d position{ 0, 0 };
		float zoomScale = 1.0f;

	public:
		Camera();

		float GetZoom() { return zoomScale; }
		olc::vi2d GetPosition() { return position; }

		void Update();
	};
}