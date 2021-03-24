#pragma once
#include "Renderer.h"
#include "GameSettings.h"

namespace RB
{
	class Timer
	{
	private:
		float fAccumulatedTime = 0.0f;

		//updates per sec
		int32_t nUpdateCount = 0;
		int32_t nUpdateCountPerSec = 0;
		float fTime = 0.0f;

	public:
		bool UpdateGame(float fElapsedTime)
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

			if (fAccumulatedTime >= GameSettings::TargetFrameTime(ChangeTimer::NONE))
			{
				fAccumulatedTime -= GameSettings::TargetFrameTime(ChangeTimer::NONE);
				nUpdateCount++;
				return true;
			}
			else
			{
				return false;
			}
		}

		void ShowUpdateCount()
		{
			RENDERER->DrawString({0, 0}, "update count: " + std::to_string(nUpdateCountPerSec), olc::WHITE);
		}
	};
}