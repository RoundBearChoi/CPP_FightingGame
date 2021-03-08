#pragma once
#include "olcPixelGameEngine.h"

namespace RB
{
	class Timer
	{
	private:
		float fTargetFrameTime = 1.0f / 120.0f; // target fixed timestep
		float fAccumulatedTime = 0.0f;

		//updates per sec
		int nUpdateCount = 0;
		int nUpdateCountPerSec = 0;
		float fTime = 0.0f;

	public:
		bool UpdateGame(float fElapsedTime, olc::PixelGameEngine* ptrEngine)
		{
			fAccumulatedTime += fElapsedTime;

			if (fTime >= 1.0f)
			{
				nUpdateCountPerSec = nUpdateCount;
				nUpdateCount = 0;
				fTime = 0.0f;
			}
			else
			{
				fTime += fElapsedTime;
			}

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

		void ShowUpdateCount(olc::PixelGameEngine* ptrEngine)
		{
			ptrEngine->DrawString({0, 0}, "update count: " + std::to_string(nUpdateCountPerSec), olc::WHITE);
		}
	};
}