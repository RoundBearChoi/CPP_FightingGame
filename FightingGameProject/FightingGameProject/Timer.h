#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class Timer
	{
	private:
		float fTargetFrameTime = 1.0f / 120.0f; // target fixed timestep
		float fAccumulatedTime = 0.0f;

		int nUpdateCount = 0;
		int nAccumulatedUpdateCount = 0;
		float fTime = 0.0f;
		olc::vf2d posCount{ 0.0f, 0.0f };

	public:
		bool UpdateGame(float fElapsedTime, olc::PixelGameEngine* ptrEngine)
		{
			fAccumulatedTime += fElapsedTime;

			if (fTime >= 1.0f)
			{
				nAccumulatedUpdateCount = nUpdateCount;
				nUpdateCount = 0;
				fTime = 0.0f;
			}
			else
			{
				fTime += fElapsedTime;
			}

			ptrEngine->DrawString(posCount, "update count: " + std::to_string(nAccumulatedUpdateCount), olc::WHITE);

			if (fAccumulatedTime >= fTargetFrameTime)
			{
				fAccumulatedTime -= fTargetFrameTime;
				nUpdateCount++;
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}