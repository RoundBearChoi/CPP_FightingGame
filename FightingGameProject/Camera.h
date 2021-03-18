#pragma once
#include "olcPixelGameEngine.h"
#include "GameSettings.h"
#include "GameData.h"

namespace RB
{
	class Camera
	{
	private:
		olc::vi2d position{ 0, 0 };
		float zoomScale = 1.0f;

	public:
		float GetZoom() { return zoomScale; }
		olc::vi2d GetPosition() { return position; }

		void Update(GameData& gameData);
	};
}